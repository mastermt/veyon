/*
 * VeyonCore.h - declaration of VeyonCore class + basic headers
 *
 * Copyright (c) 2006-2018 Tobias Junghans <tobydox@users.sf.net>
 *
 * This file is part of Veyon - http://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef VEYON_CORE_H
#define VEYON_CORE_H

#include <QtEndian>
#include <QString>
#include <QDebug>

#include <functional>

#include "QtCompat.h"

#if defined(BUILD_VEYON_CORE_LIBRARY)
#  define VEYON_CORE_EXPORT Q_DECL_EXPORT
#else
#  define VEYON_CORE_EXPORT Q_DECL_IMPORT
#endif

class QCoreApplication;
class QWidget;

class UserGroupsBackendManager;
class AuthenticationCredentials;
class CryptoCore;
class Filesystem;
class Logger;
class NetworkObjectDirectoryManager;
class PlatformPluginInterface;
class PlatformPluginManager;
class PluginManager;
class VeyonConfiguration;

// clazy:excludeall=ctor-missing-parent-argument

class VEYON_CORE_EXPORT VeyonCore : public QObject
{
	Q_OBJECT
public:
	VeyonCore( QCoreApplication* application, const QString& appComponentName );
	~VeyonCore() override;

	static VeyonCore* instance();

	static VeyonConfiguration& config()
	{
		return *( instance()->m_config );
	}

	static AuthenticationCredentials& authenticationCredentials()
	{
		return *( instance()->m_authenticationCredentials );
	}

	static PluginManager& pluginManager()
	{
		return *( instance()->m_pluginManager );
	}

	static PlatformPluginInterface& platform()
	{
		return *( instance()->m_platformPlugin );
	}

	static UserGroupsBackendManager& userGroupsBackendManager()
	{
		return *( instance()->m_userGroupsBackendManager );
	}

	static NetworkObjectDirectoryManager& networkObjectDirectoryManager()
	{
		return *( instance()->m_networkObjectDirectoryManager );
	}

	static Filesystem& filesystem()
	{
		return *( instance()->m_filesystem );
	}

	static void setupApplicationParameters();
	bool initAuthentication( int credentialTypes );

	static QString applicationName();
	static void enforceBranding( QWidget* topLevelWidget );

	static QString stripDomain( const QString& username );

	const QString& authenticationKeyName() const
	{
		return m_authenticationKeyName;
	}

	static bool isAuthenticationKeyNameValid( const QString& authKeyName );

	typedef enum AuthenticationMethods
	{
		LogonAuthentication,
		KeyFileAuthentication,
		AuthenticationMethodCount
	} AuthenticationMethod;

private:
	bool initKeyFileAuthentication();

	static VeyonCore* s_instance;

	Filesystem* m_filesystem;
	VeyonConfiguration* m_config;
	Logger* m_logger;
	AuthenticationCredentials* m_authenticationCredentials;
	CryptoCore* m_cryptoCore;
	PluginManager* m_pluginManager;
	PlatformPluginManager* m_platformPluginManager;
	PlatformPluginInterface* m_platformPlugin;
	UserGroupsBackendManager* m_userGroupsBackendManager;
	NetworkObjectDirectoryManager* m_networkObjectDirectoryManager;

	QString m_applicationName;
	QString m_authenticationKeyName;

};

#endif
