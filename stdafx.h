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
//���̷�ƮX�� ����̽�(device)��� ������ ����Ѵ�
//�� ����̽��� ���α׷��Ӱ� �׷���ī�带 �����Ҽ� �ִ� ����� �ִ� �༮�̶� �����ϸ� �ȴ�

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif

const int WINSIZEX = 1280;
const int WINSIZEY = 960;

//�Ŵ��� �߰�
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