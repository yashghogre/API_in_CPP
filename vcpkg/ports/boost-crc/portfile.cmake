# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/crc
    REF boost-${VERSION}
    SHA512 86ade360a2c4cd4e6f7e59a474838952a89275917acca1a6fcbabbf408ea82f5fcfe74ed3ff82dc528cd0d631c62d0dc7ae74a6e76ed67d756c44a79c787e9c9
    HEAD_REF master
)

set(FEATURE_OPTIONS "")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)
