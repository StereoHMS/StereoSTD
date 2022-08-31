# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget vtksys vtkCommonCore vtkCommonMath vtkCommonMisc vtkCommonSystem vtkCommonTransforms vtkCommonDataModel vtkCommonColor vtkCommonExecutionModel vtkCommonComputationalGeometry vtkFiltersCore vtkFiltersGeneral vtkImagingCore vtkImagingFourier vtkFiltersStatistics vtkFiltersExtraction vtkInfovisCore vtkFiltersGeometry vtkFiltersSources vtkRenderingCore vtkzlib vtkfreetype vtkRenderingFreeType vtkRenderingContext2D vtkChartsCore vtkDICOMParser vtkdoubleconversion vtklz4 vtklzma vtkIOCore vtkIOLegacy vtkexpat vtkIOXMLParser vtkDomainsChemistry vtkglew vtkRenderingOpenGL2 vtkDomainsChemistryOpenGL2 vtkIOXML vtkParallelCore vtkFiltersAMR vtkFiltersFlowPaths vtkFiltersGeneric vtkImagingSources vtkFiltersHybrid vtkFiltersHyperTree vtkImagingGeneral vtkFiltersImaging vtkFiltersModeling vtkFiltersParallel vtkFiltersParallelImaging vtkFiltersPoints vtkFiltersProgrammable vtkFiltersSMP vtkFiltersSelection vtkFiltersTexture vtkFiltersTopology verdict vtkFiltersVerdict vtkGUISupportMFC vtkmetaio vtkjpeg vtkpng vtktiff vtkIOImage vtkImagingHybrid vtkInfovisLayout vtkInteractionStyle vtkImagingColor vtkRenderingAnnotation vtkRenderingVolume vtkInteractionWidgets vtkViewsCore vtklibproj vtkGeovisCore vtkhdf5_src vtkhdf5_hl_src vtkIOAMR vtkIOAsynchronous vtkpugixml vtkIOCityGML vtkIOEnSight vtknetcdf vtkexodusII vtkIOExodus vtkgl2ps vtkRenderingGL2PSOpenGL2 vtkIOExport vtkIOExportOpenGL2 vtklibharu vtkIOExportPDF vtkIOGeometry vtkIOImport vtklibxml2 vtkIOInfovis vtkIOLSDyna vtkIOMINC vtkogg vtktheora vtkIOMovie vtkIONetCDF vtkIOPLY vtkjsoncpp vtkIOParallel vtkIOParallelXML vtksqlite vtkIOSQL vtkIOSegY vtkIOTecplotTable vtkIOVeraOut vtkIOVideo vtkImagingMath vtkImagingMorphological vtkImagingStatistics vtkImagingStencil vtkInteractionImage vtkRenderingContextOpenGL2 vtkRenderingExternal vtkRenderingImage vtkRenderingLOD vtkRenderingLabel vtkRenderingVolumeOpenGL2 vtkViewsContext2D vtkViewsInfovis)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target vtksys
add_library(vtksys SHARED IMPORTED)

set_target_properties(vtksys PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/vtk-8.2"
  INTERFACE_LINK_LIBRARIES "ws2_32;Psapi"
)

# Create imported target vtkCommonCore
add_library(vtkCommonCore SHARED IMPORTED)

set_target_properties(vtkCommonCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkCommonMath
add_library(vtkCommonMath SHARED IMPORTED)

set_target_properties(vtkCommonMath PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore"
)

# Create imported target vtkCommonMisc
add_library(vtkCommonMisc SHARED IMPORTED)

set_target_properties(vtkCommonMisc PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonMath"
)

# Create imported target vtkCommonSystem
add_library(vtkCommonSystem SHARED IMPORTED)

set_target_properties(vtkCommonSystem PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore"
)

# Create imported target vtkCommonTransforms
add_library(vtkCommonTransforms SHARED IMPORTED)

set_target_properties(vtkCommonTransforms PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonMath"
)

# Create imported target vtkCommonDataModel
add_library(vtkCommonDataModel SHARED IMPORTED)

set_target_properties(vtkCommonDataModel PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonMath;vtkCommonTransforms"
)

# Create imported target vtkCommonColor
add_library(vtkCommonColor SHARED IMPORTED)

set_target_properties(vtkCommonColor PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel"
)

# Create imported target vtkCommonExecutionModel
add_library(vtkCommonExecutionModel SHARED IMPORTED)

set_target_properties(vtkCommonExecutionModel PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel"
)

# Create imported target vtkCommonComputationalGeometry
add_library(vtkCommonComputationalGeometry SHARED IMPORTED)

set_target_properties(vtkCommonComputationalGeometry PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel"
)

# Create imported target vtkFiltersCore
add_library(vtkFiltersCore SHARED IMPORTED)

set_target_properties(vtkFiltersCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc"
)

# Create imported target vtkFiltersGeneral
add_library(vtkFiltersGeneral SHARED IMPORTED)

set_target_properties(vtkFiltersGeneral PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc;vtkFiltersCore"
)

# Create imported target vtkImagingCore
add_library(vtkImagingCore SHARED IMPORTED)

set_target_properties(vtkImagingCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkImagingFourier
add_library(vtkImagingFourier SHARED IMPORTED)

set_target_properties(vtkImagingFourier PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkImagingCore"
)

# Create imported target vtkFiltersStatistics
add_library(vtkFiltersStatistics SHARED IMPORTED)

set_target_properties(vtkFiltersStatistics PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkFiltersExtraction
add_library(vtkFiltersExtraction SHARED IMPORTED)

set_target_properties(vtkFiltersExtraction PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkFiltersGeneral"
)

# Create imported target vtkInfovisCore
add_library(vtkInfovisCore SHARED IMPORTED)

set_target_properties(vtkInfovisCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkFiltersGeometry
add_library(vtkFiltersGeometry SHARED IMPORTED)

set_target_properties(vtkFiltersGeometry PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkFiltersSources
add_library(vtkFiltersSources SHARED IMPORTED)

set_target_properties(vtkFiltersSources PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkRenderingCore
add_library(vtkRenderingCore SHARED IMPORTED)

set_target_properties(vtkRenderingCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMath;vtkFiltersCore"
)

# Create imported target vtkzlib
add_library(vtkzlib SHARED IMPORTED)

set_target_properties(vtkzlib PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkfreetype
add_library(vtkfreetype SHARED IMPORTED)

set_target_properties(vtkfreetype PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkzlib"
)

# Create imported target vtkRenderingFreeType
add_library(vtkRenderingFreeType SHARED IMPORTED)

set_target_properties(vtkRenderingFreeType PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkRenderingCore;vtkRenderingCore;vtkfreetype"
)

# Create imported target vtkRenderingContext2D
add_library(vtkRenderingContext2D SHARED IMPORTED)

set_target_properties(vtkRenderingContext2D PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonSystem;vtkRenderingCore"
)

# Create imported target vtkChartsCore
add_library(vtkChartsCore SHARED IMPORTED)

set_target_properties(vtkChartsCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkFiltersGeneral;vtkRenderingContext2D;vtkRenderingCore;vtksys"
)

# Create imported target vtkDICOMParser
add_library(vtkDICOMParser SHARED IMPORTED)

set_target_properties(vtkDICOMParser PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkdoubleconversion
add_library(vtkdoubleconversion SHARED IMPORTED)

set_target_properties(vtkdoubleconversion PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/vtk-8.2"
)

# Create imported target vtklz4
add_library(vtklz4 SHARED IMPORTED)

set_target_properties(vtklz4 PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "LZ4_DLL_IMPORT=1"
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtklzma
add_library(vtklzma SHARED IMPORTED)

set_target_properties(vtklzma PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOCore
add_library(vtkIOCore SHARED IMPORTED)

set_target_properties(vtkIOCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkIOLegacy
add_library(vtkIOLegacy SHARED IMPORTED)

set_target_properties(vtkIOLegacy PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkIOCore"
)

# Create imported target vtkexpat
add_library(vtkexpat SHARED IMPORTED)

set_target_properties(vtkexpat PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOXMLParser
add_library(vtkIOXMLParser SHARED IMPORTED)

set_target_properties(vtkIOXMLParser PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel"
)

# Create imported target vtkDomainsChemistry
add_library(vtkDomainsChemistry SHARED IMPORTED)

set_target_properties(vtkDomainsChemistry PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkIOLegacy;vtkIOXMLParser;vtkRenderingCore"
)

# Create imported target vtkglew
add_library(vtkglew SHARED IMPORTED)

set_target_properties(vtkglew PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkRenderingOpenGL2
add_library(vtkRenderingOpenGL2 SHARED IMPORTED)

set_target_properties(vtkRenderingOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkRenderingCore;vtkRenderingCore"
)

# Create imported target vtkDomainsChemistryOpenGL2
add_library(vtkDomainsChemistryOpenGL2 SHARED IMPORTED)

set_target_properties(vtkDomainsChemistryOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkDomainsChemistry;vtkDomainsChemistry;vtkRenderingOpenGL2"
)

# Create imported target vtkIOXML
add_library(vtkIOXML SHARED IMPORTED)

set_target_properties(vtkIOXML PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOXMLParser"
)

# Create imported target vtkParallelCore
add_library(vtkParallelCore SHARED IMPORTED)

set_target_properties(vtkParallelCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore"
)

# Create imported target vtkFiltersAMR
add_library(vtkFiltersAMR SHARED IMPORTED)

set_target_properties(vtkFiltersAMR PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkFiltersFlowPaths
add_library(vtkFiltersFlowPaths SHARED IMPORTED)

set_target_properties(vtkFiltersFlowPaths PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMath"
)

# Create imported target vtkFiltersGeneric
add_library(vtkFiltersGeneric SHARED IMPORTED)

set_target_properties(vtkFiltersGeneric PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkCommonMath"
)

# Create imported target vtkImagingSources
add_library(vtkImagingSources SHARED IMPORTED)

set_target_properties(vtkImagingSources PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkFiltersHybrid
add_library(vtkFiltersHybrid SHARED IMPORTED)

set_target_properties(vtkFiltersHybrid PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonTransforms"
)

# Create imported target vtkFiltersHyperTree
add_library(vtkFiltersHyperTree SHARED IMPORTED)

set_target_properties(vtkFiltersHyperTree PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc;vtkFiltersCore"
)

# Create imported target vtkImagingGeneral
add_library(vtkImagingGeneral SHARED IMPORTED)

set_target_properties(vtkImagingGeneral PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkImagingCore"
)

# Create imported target vtkFiltersImaging
add_library(vtkFiltersImaging SHARED IMPORTED)

set_target_properties(vtkFiltersImaging PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkFiltersStatistics"
)

# Create imported target vtkFiltersModeling
add_library(vtkFiltersModeling SHARED IMPORTED)

set_target_properties(vtkFiltersModeling PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkCommonMisc;vtkFiltersGeneral"
)

# Create imported target vtkFiltersParallel
add_library(vtkFiltersParallel SHARED IMPORTED)

set_target_properties(vtkFiltersParallel PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkFiltersCore;vtkFiltersExtraction;vtkFiltersGeneral;vtkFiltersGeometry;vtkFiltersModeling;vtkFiltersSources"
)

# Create imported target vtkFiltersParallelImaging
add_library(vtkFiltersParallelImaging SHARED IMPORTED)

set_target_properties(vtkFiltersParallelImaging PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkFiltersImaging;vtkFiltersParallel;vtkImagingCore"
)

# Create imported target vtkFiltersPoints
add_library(vtkFiltersPoints SHARED IMPORTED)

set_target_properties(vtkFiltersPoints PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkFiltersModeling"
)

# Create imported target vtkFiltersProgrammable
add_library(vtkFiltersProgrammable SHARED IMPORTED)

set_target_properties(vtkFiltersProgrammable PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkFiltersSMP
add_library(vtkFiltersSMP SHARED IMPORTED)

set_target_properties(vtkFiltersSMP PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc;vtkCommonTransforms;vtkFiltersCore;vtkFiltersGeneral"
)

# Create imported target vtkFiltersSelection
add_library(vtkFiltersSelection SHARED IMPORTED)

set_target_properties(vtkFiltersSelection PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkFiltersTexture
add_library(vtkFiltersTexture SHARED IMPORTED)

set_target_properties(vtkFiltersTexture PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkFiltersTopology
add_library(vtkFiltersTopology SHARED IMPORTED)

set_target_properties(vtkFiltersTopology PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target verdict
add_library(verdict SHARED IMPORTED)

# Create imported target vtkFiltersVerdict
add_library(vtkFiltersVerdict SHARED IMPORTED)

set_target_properties(vtkFiltersVerdict PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;verdict"
)

# Create imported target vtkGUISupportMFC
add_library(vtkGUISupportMFC SHARED IMPORTED)

set_target_properties(vtkGUISupportMFC PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkRenderingOpenGL2"
)

# Create imported target vtkmetaio
add_library(vtkmetaio SHARED IMPORTED)

set_target_properties(vtkmetaio PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib;comctl32;wsock32"
)

# Create imported target vtkjpeg
add_library(vtkjpeg SHARED IMPORTED)

set_target_properties(vtkjpeg PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkpng
add_library(vtkpng SHARED IMPORTED)

set_target_properties(vtkpng PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtktiff
add_library(vtktiff SHARED IMPORTED)

set_target_properties(vtktiff PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOImage
add_library(vtkIOImage SHARED IMPORTED)

set_target_properties(vtkIOImage PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkImagingHybrid
add_library(vtkImagingHybrid SHARED IMPORTED)

set_target_properties(vtkImagingHybrid PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkInfovisLayout
add_library(vtkInfovisLayout SHARED IMPORTED)

set_target_properties(vtkInfovisLayout PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkInteractionStyle
add_library(vtkInteractionStyle SHARED IMPORTED)

set_target_properties(vtkInteractionStyle PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkRenderingCore;vtkRenderingCore"
)

# Create imported target vtkImagingColor
add_library(vtkImagingColor SHARED IMPORTED)

set_target_properties(vtkImagingColor PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkImagingCore"
)

# Create imported target vtkRenderingAnnotation
add_library(vtkRenderingAnnotation SHARED IMPORTED)

set_target_properties(vtkRenderingAnnotation PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkRenderingCore"
)

# Create imported target vtkRenderingVolume
add_library(vtkRenderingVolume SHARED IMPORTED)

set_target_properties(vtkRenderingVolume PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkRenderingCore"
)

# Create imported target vtkInteractionWidgets
add_library(vtkInteractionWidgets SHARED IMPORTED)

set_target_properties(vtkInteractionWidgets PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkFiltersGeneral;vtkFiltersSources;vtkRenderingCore"
)

# Create imported target vtkViewsCore
add_library(vtkViewsCore SHARED IMPORTED)

set_target_properties(vtkViewsCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkInteractionWidgets"
)

# Create imported target vtklibproj
add_library(vtklibproj SHARED IMPORTED)

set_target_properties(vtklibproj PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkGeovisCore
add_library(vtkGeovisCore SHARED IMPORTED)

set_target_properties(vtkGeovisCore PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonTransforms;vtkInfovisCore;vtkInteractionStyle;vtkInteractionWidgets;vtkRenderingCore;vtkViewsCore;vtklibproj"
)

# Create imported target vtkhdf5_src
add_library(vtkhdf5_src SHARED IMPORTED)

set_target_properties(vtkhdf5_src PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "H5_BUILT_AS_DYNAMIC_LIB"
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkhdf5_hl_src
add_library(vtkhdf5_hl_src SHARED IMPORTED)

set_target_properties(vtkhdf5_hl_src PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "H5_BUILT_AS_DYNAMIC_LIB"
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOAMR
add_library(vtkIOAMR SHARED IMPORTED)

set_target_properties(vtkIOAMR PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkIOAsynchronous
add_library(vtkIOAsynchronous SHARED IMPORTED)

set_target_properties(vtkIOAsynchronous PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOCore;vtkIOImage;vtkIOXML"
)

# Create imported target vtkpugixml
add_library(vtkpugixml SHARED IMPORTED)

set_target_properties(vtkpugixml PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOCityGML
add_library(vtkIOCityGML SHARED IMPORTED)

set_target_properties(vtkIOCityGML PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkFiltersGeneral;vtkFiltersModeling;vtkpugixml"
)

# Create imported target vtkIOEnSight
add_library(vtkIOEnSight SHARED IMPORTED)

set_target_properties(vtkIOEnSight PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtknetcdf
add_library(vtknetcdf SHARED IMPORTED)

set_target_properties(vtknetcdf PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkhdf5_src;vtkhdf5_hl_src"
)

# Create imported target vtkexodusII
add_library(vtkexodusII SHARED IMPORTED)

set_target_properties(vtkexodusII PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtknetcdf"
)

# Create imported target vtkIOExodus
add_library(vtkIOExodus SHARED IMPORTED)

set_target_properties(vtkIOExodus PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkIOCore;vtkIOXMLParser;vtkexodusII"
)

# Create imported target vtkgl2ps
add_library(vtkgl2ps SHARED IMPORTED)

set_target_properties(vtkgl2ps PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkpng;vtkzlib"
)

# Create imported target vtkRenderingGL2PSOpenGL2
add_library(vtkRenderingGL2PSOpenGL2 SHARED IMPORTED)

set_target_properties(vtkRenderingGL2PSOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkRenderingOpenGL2;vtkRenderingOpenGL2"
)

# Create imported target vtkIOExport
add_library(vtkIOExport SHARED IMPORTED)

set_target_properties(vtkIOExport PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkIOCore;vtkIOImage;vtkIOXML;vtkRenderingContext2D;vtkRenderingCore;vtkRenderingFreeType;vtkRenderingGL2PSOpenGL2"
)

# Create imported target vtkIOExportOpenGL2
add_library(vtkIOExportOpenGL2 SHARED IMPORTED)

set_target_properties(vtkIOExportOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkIOExport;vtkIOExport;vtkRenderingGL2PSOpenGL2"
)

# Create imported target vtklibharu
add_library(vtklibharu SHARED IMPORTED)

set_target_properties(vtklibharu PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOExportPDF
add_library(vtkIOExportPDF SHARED IMPORTED)

set_target_properties(vtkIOExportPDF PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkIOExport;vtkIOExport"
)

# Create imported target vtkIOGeometry
add_library(vtkIOGeometry SHARED IMPORTED)

set_target_properties(vtkIOGeometry PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkIOCore;vtkIOLegacy"
)

# Create imported target vtkIOImport
add_library(vtkIOImport SHARED IMPORTED)

set_target_properties(vtkIOImport PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkCommonMisc;vtkRenderingCore;vtksys"
)

# Create imported target vtklibxml2
add_library(vtklibxml2 SHARED IMPORTED)

set_target_properties(vtklibxml2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkzlib"
)

# Create imported target vtkIOInfovis
add_library(vtkIOInfovis SHARED IMPORTED)

set_target_properties(vtkIOInfovis PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOLegacy;vtkIOXML"
)

# Create imported target vtkIOLSDyna
add_library(vtkIOLSDyna SHARED IMPORTED)

set_target_properties(vtkIOLSDyna PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOXMLParser"
)

# Create imported target vtkIOMINC
add_library(vtkIOMINC SHARED IMPORTED)

set_target_properties(vtkIOMINC PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOCore;vtkIOImage"
)

# Create imported target vtkogg
add_library(vtkogg SHARED IMPORTED)

set_target_properties(vtkogg PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/vtk-8.2/vtkogg/include"
)

# Create imported target vtktheora
add_library(vtktheora SHARED IMPORTED)

set_target_properties(vtktheora PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkogg"
)

# Create imported target vtkIOMovie
add_library(vtkIOMovie SHARED IMPORTED)

set_target_properties(vtkIOMovie PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtktheora"
)

# Create imported target vtkIONetCDF
add_library(vtkIONetCDF SHARED IMPORTED)

set_target_properties(vtkIONetCDF PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkIOPLY
add_library(vtkIOPLY SHARED IMPORTED)

set_target_properties(vtkIOPLY PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkIOCore"
)

# Create imported target vtkjsoncpp
add_library(vtkjsoncpp SHARED IMPORTED)

set_target_properties(vtkjsoncpp PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOParallel
add_library(vtkIOParallel SHARED IMPORTED)

set_target_properties(vtkIOParallel PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkIOCore;vtkIOGeometry;vtkIOImage;vtkIOLegacy;vtkIONetCDF"
)

# Create imported target vtkIOParallelXML
add_library(vtkIOParallelXML SHARED IMPORTED)

set_target_properties(vtkIOParallelXML PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkIOXML"
)

# Create imported target vtksqlite
add_library(vtksqlite SHARED IMPORTED)

set_target_properties(vtksqlite PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
)

# Create imported target vtkIOSQL
add_library(vtkIOSQL SHARED IMPORTED)

set_target_properties(vtkIOSQL PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel;vtkIOCore"
)

# Create imported target vtkIOSegY
add_library(vtkIOSegY SHARED IMPORTED)

set_target_properties(vtkIOSegY PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkIOImage"
)

# Create imported target vtkIOTecplotTable
add_library(vtkIOTecplotTable SHARED IMPORTED)

set_target_properties(vtkIOTecplotTable PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonExecutionModel"
)

# Create imported target vtkIOVeraOut
add_library(vtkIOVeraOut SHARED IMPORTED)

set_target_properties(vtkIOVeraOut PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkIOVideo
add_library(vtkIOVideo SHARED IMPORTED)

set_target_properties(vtkIOVideo PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkImagingMath
add_library(vtkImagingMath SHARED IMPORTED)

set_target_properties(vtkImagingMath PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkImagingMorphological
add_library(vtkImagingMorphological SHARED IMPORTED)

set_target_properties(vtkImagingMorphological PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkImagingCore;vtkImagingGeneral"
)

# Create imported target vtkImagingStatistics
add_library(vtkImagingStatistics SHARED IMPORTED)

set_target_properties(vtkImagingStatistics PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkImagingStencil
add_library(vtkImagingStencil SHARED IMPORTED)

set_target_properties(vtkImagingStencil PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkImagingCore"
)

# Create imported target vtkInteractionImage
add_library(vtkInteractionImage SHARED IMPORTED)

set_target_properties(vtkInteractionImage PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkRenderingCore"
)

# Create imported target vtkRenderingContextOpenGL2
add_library(vtkRenderingContextOpenGL2 SHARED IMPORTED)

set_target_properties(vtkRenderingContextOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkRenderingContext2D;vtkRenderingContext2D;vtkRenderingCore;vtkRenderingFreeType;vtkRenderingOpenGL2"
)

# Create imported target vtkRenderingExternal
add_library(vtkRenderingExternal SHARED IMPORTED)

set_target_properties(vtkRenderingExternal PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkRenderingCore;vtkRenderingOpenGL2"
)

# Create imported target vtkRenderingImage
add_library(vtkRenderingImage SHARED IMPORTED)

set_target_properties(vtkRenderingImage PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkRenderingCore"
)

# Create imported target vtkRenderingLOD
add_library(vtkRenderingLOD SHARED IMPORTED)

set_target_properties(vtkRenderingLOD PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkRenderingCore"
)

# Create imported target vtkRenderingLabel
add_library(vtkRenderingLabel SHARED IMPORTED)

set_target_properties(vtkRenderingLabel PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkRenderingCore;vtkRenderingFreeType"
)

# Create imported target vtkRenderingVolumeOpenGL2
add_library(vtkRenderingVolumeOpenGL2 SHARED IMPORTED)

set_target_properties(vtkRenderingVolumeOpenGL2 PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkImagingCore;vtkImagingMath;vtkRenderingCore;vtkRenderingOpenGL2;vtkRenderingVolume;vtkRenderingVolume;vtkglew"
)

# Create imported target vtkViewsContext2D
add_library(vtkViewsContext2D SHARED IMPORTED)

set_target_properties(vtkViewsContext2D PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkRenderingCore;vtkViewsCore"
)

# Create imported target vtkViewsInfovis
add_library(vtkViewsInfovis SHARED IMPORTED)

set_target_properties(vtkViewsInfovis PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_nullptr;cxx_override"
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonDataModel;vtkCommonExecutionModel;vtkInteractionStyle;vtkRenderingContext2D;vtkViewsCore"
)

if(CMAKE_VERSION VERSION_LESS 2.8.12)
  message(FATAL_ERROR "This file relies on consumers using CMake 2.8.12 or greater.")
endif()

# Load information for each installed configuration.
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/VTKTargets-*.cmake")
foreach(f ${CONFIG_FILES})
  include(${f})
endforeach()

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(target ${_IMPORT_CHECK_TARGETS} )
  foreach(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    if(NOT EXISTS "${file}" )
      message(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
  endforeach()
  unset(_IMPORT_CHECK_FILES_FOR_${target})
endforeach()
unset(_IMPORT_CHECK_TARGETS)

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
