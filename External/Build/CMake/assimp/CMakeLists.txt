SET(ASSIMP_PROJECT_DIR "${EXTERNAL_PROJECT_DIR}/assimp")
SET(ASSIMP_OUTPUT_DIR "${EXTERNAL_PROJECT_DIR}/lib/assimp/${KLAYGE_PLATFORM_NAME}")

UpdateExternalLib("assimp" "https://github.com/assimp/assimp.git" "8c15a35609e8582945aec966f263d0ee821d63ae" "master" "v4.1.0")

FOREACH(flag_var
		CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_MINSIZEREL)
	STRING(REPLACE "${NO_RTTI_FLAG}" "${RTTI_FLAG}" ${flag_var} "${${flag_var}}")
ENDFOREACH()

IF(MINGW)
	# To fix a problem that Importer/StepFile/StepFileGen1.cpp is too big
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")
ENDIF()

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ASSIMP_OPT_BUILD_PACKAGES OFF CACHE BOOL "" FORCE)
set(ASSIMP_ANDROID_JNIIOSYSTEM OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_NONFREE_C4D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
set(IGNORE_GIT_HASH ON CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY(${ASSIMP_PROJECT_DIR} "${CMAKE_CURRENT_BINARY_DIR}/assimp")

SET_TARGET_PROPERTIES(assimp PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${ASSIMP_OUTPUT_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ASSIMP_OUTPUT_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ASSIMP_OUTPUT_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${ASSIMP_OUTPUT_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${ASSIMP_OUTPUT_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${KLAYGE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${KLAYGE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${KLAYGE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${KLAYGE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${KLAYGE_BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY ${KLAYGE_BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${KLAYGE_BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${KLAYGE_BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${KLAYGE_BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${KLAYGE_BIN_DIR}
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	OUTPUT_NAME assimp${KLAYGE_OUTPUT_SUFFIX}
)

add_dependencies(assimp ${KLAYGE_ZLIB_NAME})

foreach(target
	"assimp" "IrrXML" "uninstall")
	set_target_properties(${target} PROPERTIES FOLDER "${EXTERNAL_VS_FOLDER_PREFIX}/assimp")
endforeach()
if(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs)
	set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "${EXTERNAL_VS_FOLDER_PREFIX}/assimp")
endif()
