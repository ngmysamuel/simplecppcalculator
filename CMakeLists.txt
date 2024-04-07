########################################################################################################################
### SIMPLEHTTPSERVER LIBRARY MAIN
########################################################################################################################

cmake_minimum_required(VERSION 3.2)

########################################################################################################################
### PROJECT DESCRIPTION AND META INFO
########################################################################################################################

set(SIMPLEHTTPSERVER_PROJECT_NAME        "simplecppcalculator")
set(SIMPLEHTTPSERVER_PROJECT_DESCRIPTION "A simple calculator which you call by making GET requests")
set(SIMPLEHTTPSERVER_AUTHOR_DOMAIN       "https://github.com/ngmysamuel")
set(SIMPLEHTTPSERVER_AUTHOR_MAINTAINER   "e0148675")
set(SIMPLEHTTPSERVER_VERSION_MAJOR       "0")
set(SIMPLEHTTPSERVER_VERSION_MINOR       "0")
set(SIMPLEHTTPSERVER_VERSION_PATCH       "1")

set(SIMPLEHTTPSERVER_VERSION
    "${SIMPLEHTTPSERVER_VERSION_MAJOR}.${SIMPLEHTTPSERVER_VERSION_MINOR}.${SIMPLEHTTPSERVER_VERSION_PATCH}")
set(SIMPLEHTTPSERVER_NAME_VERSION
    "${SIMPLEHTTPSERVER_PROJECT_NAME} v${SIMPLEHTTPSERVER_VERSION} (${SIMPLEHTTPSERVER_VERSION_REVISION})")

########################################################################################################################
### DECLARE PROJECT
########################################################################################################################

project(${SIMPLEHTTPSERVER_PROJECT_NAME})

set(SIMPLEHTTPSERVER_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)