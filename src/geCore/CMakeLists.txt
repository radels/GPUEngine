cmake_minimum_required (VERSION 2.6)
SET(LIB_NAME geCore)

SET(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set( CORE_INCLUDES
		${HEADER_PATH}/Export.h
		${HEADER_PATH}/Object.h
      ${HEADER_PATH}/CopyOp.h
  )
  
 set( CORE_SOURCES
		Object.cpp
      CopyOp.cpp
	)
	
ADD_LIBRARY(${LIB_NAME} 
		${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
		${CORE_INCLUDES}
		${CORE_SOURCES}
	)


#install(FILES
#  ${OGL_INCLUDES}
#  DESTINATION include/ge/${LIB_NAME}
#  )
#
#install(TARGETS ${LIB_NAME}
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#  )