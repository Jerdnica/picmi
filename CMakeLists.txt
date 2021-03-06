cmake_minimum_required (VERSION 2.8.12)
project (picmi)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()


find_package(ECM 1.7.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 5.2.0 CONFIG REQUIRED Core Widgets Svg Quick QuickWidgets Test)
find_package(KF5 REQUIRED COMPONENTS
    DocTools
    CoreAddons
    DBusAddons
    Declarative
    DocTools
    I18n
    KIO
    NewStuff
    XmlGui
)

find_package(KF5KDEGames 5.2.0 REQUIRED)

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(FeatureSummary)
include(ECMAddAppIcon)
include(ECMInstallIcons)
include(ECMAddTests)


add_subdirectory(themes)
add_subdirectory(icons)
add_subdirectory(doc)
add_subdirectory(levels)
add_subdirectory(src)
add_subdirectory(test)

install(FILES ${CMAKE_SOURCE_DIR}/org.kde.picmi.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES ${CMAKE_SOURCE_DIR}/org.kde.picmi.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR} )
install(FILES ${CMAKE_SOURCE_DIR}/picmiui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/picmi)

# vim:set ts=4 sw=4 et:
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
