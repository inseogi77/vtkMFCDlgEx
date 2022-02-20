// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"


// vtk header
#include <vtkAutoInit.h>
#define vtkRenderingCore_AUTOINIT 3(vtkRenderingOpenGL2, vtkInteractionStyle, vtkRenderingFreeType)
#define vtkRenderingContext2D_AUTOINIT 1(vtkRenderingContextOpenGL2)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkConeSource.h>

#include <vtkAbstractWidget.h>
#include <vtkAngleWidget.h>
#include <vtkImagePlaneWidget.h>
#include <vtkCaptionWidget.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkTextWidget.h>
#include <vtkCamera.h>
#include <vtkLight.h>

#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkArrowSource.h>

#include <vtkSTLReader.h>
#include <vtkSTLWriter.h >
#include <vtkProperty.h>

#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>

#endif //PCH_H
