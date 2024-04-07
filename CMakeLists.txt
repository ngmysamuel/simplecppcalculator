########################################################################################################################
### SIMPLECPPCALCULATOR LIBRARY MAIN
########################################################################################################################

cmake_minimum_required(VERSION 3.2)

########################################################################################################################
### PROJECT DESCRIPTION AND META INFO
########################################################################################################################

set(SIMPLECPPCALCULATOR_PROJECT_NAME        "simplecppcalculator")
set(SIMPLECPPCALCULATOR_PROJECT_DESCRIPTION "A simple calculator which you call by making GET requests")
set(SIMPLECPPCALCULATOR_AUTHOR_DOMAIN       "https://github.com/ngmysamuel")
set(SIMPLECPPCALCULATOR_AUTHOR_MAINTAINER   "e0148675")
set(SIMPLECPPCALCULATOR_VERSION_MAJOR       "0")
set(SIMPLECPPCALCULATOR_VERSION_MINOR       "0")
set(SIMPLECPPCALCULATOR_VERSION_PATCH       "1")

set(SIMPLECPPCALCULATOR_VERSION
    "${SIMPLECPPCALCULATOR_VERSION_MAJOR}.${SIMPLECPPCALCULATOR_VERSION_MINOR}.${SIMPLECPPCALCULATOR_VERSION_PATCH}")
set(SIMPLECPPCALCULATOR_NAME_VERSION
    "${SIMPLECPPCALCULATOR_PROJECT_NAME} v${SIMPLECPPCALCULATOR_VERSION} (${SIMPLECPPCALCULATOR_VERSION_REVISION})")

########################################################################################################################
### DECLARE PROJECT
########################################################################################################################

project(${SIMPLECPPCALCULATOR_PROJECT_NAME})

set(SIMPLECPPCALCULATOR_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)