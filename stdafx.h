#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <queue>
#include "Lib/FMod/inc/fmod.hpp"
#include "Lib/FMod/inc/fmod_errors.h"
#pragma comment(lib, "./Lib/FMod/lib/x64/fmod_vc.lib")

#include "cMath.h"

using namespace std;
using namespace Math;
using namespace FMOD;

#define g_device DXUTGetD3D9Device()
//다이렉트X는 디바이스(device)라는 개념을 사용한다
//이 디바이스는 프로그래머가 그래픽카드를 제어할수 있는 방법을 주는 녀석이라 생각하면 된다

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif

const int WINSIZEX = 1280;
const int WINSIZEY = 960;

//매니저 추가
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cEffectManager.h"
#include "cEffect.h"
#include "cSystemManager.h"
#include "cInputManager.h"


#include "cRenderer.h"
#include "cAnimation.h"
#include "cAnimator.h"
#include "cBoxCollider.h"
#include "cCircleCollider.h"
#include "cPath.h"

using Vector2 = D3DXVECTOR2;
#define DeltaTime DXUTGetElapsedTime()