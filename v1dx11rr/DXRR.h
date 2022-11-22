#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include "GUI.h"
#include "Text.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <list>

using namespace std;

class DXRR {

private:
	int ancho;
	int alto;
public:
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState* alphaBlendState, * commonBlendState;

	GUI* fullVida;
	GUI* middleVida;
	GUI* endVida;
	GUI* gameOver;
	GUI* ganador;
	GUI* cruz;
	GUI* balasFull;
	GUI* balas3;
	GUI* balas2;
	GUI* balas1;
	GUI* balasEmpty;

	int frameBillboard;

	TerrenoRR* terreno;
	SkyDome* skydome;
	BillboardRR* billboard;
	BillboardRR* billArbol;
	BillboardRR* billArbusto;
	Camara* camara;
	ModeloRR* cantina;
	ModeloRR* caballoNegro;
	ModeloRR* caballoBlanco;
	ModeloRR* vagon;
	ModeloRR* molino;
	ModeloRR* barrel;
	ModeloRR* carreta;
	ModeloRR* tronco;
	ModeloRR* enemigo1;
	ModeloRR* pistola;
	ModeloRR* carril;
	ModeloRR* tronco1;
	ModeloRR* tronco2;
	ModeloRR* bala;
	ModeloRR* bala1;
	ModeloRR* bala2;
	ModeloRR* bala3;
	ModeloRR* bala4;
	ModeloRR* bala5;

	float rotCam;
	float rotCamX;
	float balaRespuesta;
	float izqder;
	float arriaba;
	float vel;
	bool breakpoint;
	bool retraso;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];
	bool setCamaraTipo;
	bool playRevolver;
	bool playGame = true;
	bool ocultarBala1;
	bool ocultarBala2;
	bool ocultarBala3;
	bool ocultarBala4;
	bool ocultarBala5;

	bool ocultarEnemigo1;
	bool ocultarEnemigo2;
	bool ocultarEnemigo3;
	bool ocultarEnemigo4;
	bool ocultarEnemigo5;

	Text* texto;
	Text* textoBalas;

	int vidas;
	int balas;
	float elevacionModelo;
	float movBala;
	bool movBalabool;

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	float segundos;

	float movEnemigo1X;
	float movEnemigo1Z;
	bool movEnemigo1Dir;

	float rotxAux, rotyAux, zbalaAux, ybalaAux, xbalaAux;

	list<ModeloRR*> balasList;

	DXRR(HWND hWnd, int Ancho, int Alto)
	{
		ocultarEnemigo1 = false;
		ocultarEnemigo2 = false;
		ocultarEnemigo3 = false;
		ocultarEnemigo4 = false;
		ocultarEnemigo5 = false;
		rotxAux = 0.0f;
		rotyAux = 0.0f;
		movBalabool = false;
		movBala = 0.0f;
		movEnemigo1Dir = false;
		movEnemigo1X = 0;
		movEnemigo1Z = 0;
		ocultarBala1 = false;
		ocultarBala2 = false;
		ocultarBala3 = false;
		ocultarBala4 = false;
		ocultarBala5 = false;
		elevacionModelo = 1.0f;
		balas = 4;
		segundos = 301;
		retraso = false;
		vidas = 3;
		balaRespuesta = 0.0f;
		rotCam = 0;
		rotCamX = 0;
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		camara = new Camara(D3DXVECTOR3(0, 80, 6), D3DXVECTOR3(0, 80, 0), D3DXVECTOR3(0, 1, 0), Ancho, Alto);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"SkyDome34.png");
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
																													   /*BILLBOARDS*/
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png", L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		billArbol = new BillboardRR(L"Assets/Billboards/arbol.png", L"Assets/Billboards/arbol_normal.png", d3dDevice, d3dContext, 6);
		billArbusto = new BillboardRR(L"Assets/Billboards/arbusto.png", L"Assets/Billboards/arbusto_normal.png", d3dDevice, d3dContext, 6);
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
																													   /*MODELOS*/
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		cantina = new ModeloRR(d3dDevice, d3dContext, "Assets/saloon/Saloon (1).obj", L"Assets/saloon/saloonUVSCOLORFINAL.jpg", L"Assets/saloon/saloonUVSCOLORFINAL.jpg", L"Assets/saloon/saloonUVSNORMALFINAL.png", 59, -90);

		molino = new ModeloRR(d3dDevice, d3dContext, "Assets/molino/molino_sis.obj", L"Assets/molino/molinocolor.jpg", L"Assets/molino/molinocolor.jpg", L"Assets/molino/molinonormal.png", 77, 106);
		tronco = new ModeloRR(d3dDevice, d3dContext, "Assets/tronco/troncoprueba.obj", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotexnormal.png", -55, 40);
		tronco1 = new ModeloRR(d3dDevice, d3dContext, "Assets/tronco/troncoprueba.obj", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotexnormal.png", -55, 46);
		tronco2 = new ModeloRR(d3dDevice, d3dContext, "Assets/tronco/troncoprueba.obj", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotex.png", L"Assets/tronco/arboltrotexnormal.png", -55, 43);
		vagon = new ModeloRR(d3dDevice, d3dContext, "Assets/vagon/vagon.obj", L"Assets/vagon/miltrenCOLOR.jpg", L"Assets/vagon/miltrenCOLOR.jpg", L"Assets/vagon/miltrenCOLORnormal.png", -55, -41);
		caballoNegro = new ModeloRR(d3dDevice, d3dContext, "Assets/horse/horse-obj.obj", L"Assets/horse/horseuvscolor.jpg", L"Assets/horse/horseuvscolor.jpg", L"Assets/horse/horseuvscolornormal.png", -100, -99);
		caballoBlanco = new ModeloRR(d3dDevice, d3dContext, "Assets/horse/horseblanco.obj", L"Assets/horse/horseuvsblanco.jpg", L"Assets/horse/horseuvsblanco.jpg", L"Assets/horse/horseuvsblanconormal.png", camara->hdveo.x, camara->hdveo.z);
		carreta = new ModeloRR(d3dDevice, d3dContext, "Assets/carreta/carreta_obj.obj", L"Assets/carreta/carretauvsCOLOR.jpg", L"Assets/carreta/carretauvsCOLOR.jpg", L"Assets/carreta/carretauvsCOLORnormal.png", 80, 15);
		carril = new ModeloRR(d3dDevice, d3dContext, "Assets/carril/carril.obj", L"Assets/carril/METAL.jpg", L"Assets/carril/METAL.jpg", L"Assets/carril/METALnormal.png", -60, -29);
		barrel = new ModeloRR(d3dDevice, d3dContext, "Assets/barrel/Barrel.obj", L"Assets/barrel/barreluvscolor.jpg", L"Assets/barrel/barreluvscolor.jpg", L"Assets/barrel/barreluvscolornormal.png", 34, 30);
		enemigo1 = new ModeloRR(d3dDevice, d3dContext, "Assets/enemigo/enemigo.obj", L"Assets/enemigo/enemigo.png", L"Assets/enemigo/enemigo.png", L"Assets/enemigo/enemigo_norm.png", 30, 30);
		pistola = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/Colt_Python.obj", L"Assets/guns/gunsuvscolorfinalFINAL.jpg", L"Assets/guns/gunsuvscolorfinalFINAL.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", 0.0f, 0.0f);

		bala = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", camara->hdveo.x, camara->hdveo.z);
		bala1 = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", -20, 0.0);
		bala2 = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", 100, -50);
		bala3 = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", -100, 50);
		bala4 = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", 120, 80);
		bala5 = new ModeloRR(d3dDevice, d3dContext, "Assets/guns/bullet.obj", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/miltrenCOLOR.jpg", L"Assets/guns/gunsuvscolorfinalFINALnormal.png", -120, -60);

		fullVida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/vidas/health_full.png");
		middleVida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/vidas/health_2.png");
		endVida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/vidas/health_1.png");
		gameOver = new GUI(d3dDevice, d3dContext, 1, 1, L"Assets/gameover/game_over.png");
		ganador = new GUI(d3dDevice, d3dContext, 1, 1, L"Assets/ganador/ganador.png");
		cruz = new GUI(d3dDevice, d3dContext, 0.1, 0.05, L"Assets/cruz/cruz.png");
		balasFull = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/balas/balas_full.png");
		balas3 = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/balas/balas_3.png");
		balas2 = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/balas/balas_2.png");
		balas1 = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/balas/balas_1.png");
		balasEmpty = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/balas/balas_empty.png");

		texto = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/Texto/font.jpg", XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		textoBalas = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/Texto/font.jpg", XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

		setCamaraTipo = false;
		playRevolver = false;

		for (int i = 0; i < 4; i++)
			balasList.push_back(bala);
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}

	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for (driver = 0; driver < totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels,
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if (SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if (FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}

		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if (FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if (backBufferTexture)
			backBufferTexture->Release();

		if (FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		//XACT
		bool res = m_XACT3.Initialize();
		if (!res) return false;

		res = m_XACT3.LoadWaveBank(L"Assets\\audio\\WaveBank.xwb");
		if (!res) return false;

		res = m_XACT3.LoadSoundBank(L"Assets\\audio\\SoundBank.xsb");
		if (!res) return false;
		//Reproducir
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("revolver");

		return true;

	}

	void LiberaD3D(void)
	{
		if (depthTexture)
			depthTexture->Release();
		if (depthStencilView)
			depthStencilView->Release();
		if (backBufferTarget)
			backBufferTarget->Release();
		if (swapChain)
			swapChain->Release();
		if (d3dContext)
			d3dContext->Release();
		if (d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}

	void Render(void)
	{

		if (!movEnemigo1Dir)
			movEnemigo1X += 0.001;
		if (movEnemigo1Dir)
			movEnemigo1X -= 0.001;

		if (movEnemigo1X >= 0.3)
			movEnemigo1Dir = true;
		if (movEnemigo1X <= -0.3)
			movEnemigo1Dir = false;

		elevacionModelo += 0.08f;

		if (elevacionModelo >= 4.0f)
			elevacionModelo = 1.0f;
		retraso = true;
		rotCam += izqder;

		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if (d3dContext == 0)
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView(backBufferTarget, clearColor);
		d3dContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 10;
		camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 15;
		camara->UpdateCam(vel, arriaba, izqder, this->setCamaraTipo);

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		if (this->setCamaraTipo)
			skydome->Render(camara->posCam);
		else
			skydome->Render(camara->posCam3P);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);
		if (playRevolver && balas >= 1)
		{
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
			movBalabool = true;
			balas -= 1;
			balasList.pop_back();
		}

		if (setCamaraTipo) {
			/*---------------------------------------------------------------------------*/
			/*                                                 Billboards                                                  */
			/*---------------------------------------------------------------------------*/
				/*ARBOLES*/
			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				20, -83, terreno->Superficie(20, -83) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				100, -85, terreno->Superficie(100, -85) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-100, -60, terreno->Superficie(-100, -60) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-30, 40, terreno->Superficie(-30, 40) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				50, 90, terreno->Superficie(50, 90) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
				90, 0, terreno->Superficie(90, 0) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);


			/*ARBUSTOS*/
			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				20, 0, terreno->Superficie(20, 0) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				80, 30, terreno->Superficie(80, 30) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				100, -40, terreno->Superficie(100, -40) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-40, -60, terreno->Superficie(-40, -60) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-40, 100, terreno->Superficie(-40, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-80, 80, terreno->Superficie(-80, 80) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-80, 100, terreno->Superficie(-80, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
				80, 100, terreno->Superficie(-80, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);
			/*---------------------------------------------------------------------------*/
			/*                                                 COLISIONES                                              */
			/*---------------------------------------------------------------------------*/
			//Cantina
			if (isPointInsideSphere(camara->getPoint(), cantina->getSphere(25.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Molino
			if (isPointInsideSphere(camara->getPoint(), molino->getSphere(10.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Carreta
			if (isPointInsideSphere(camara->getPoint(), tronco1->getSphere(12.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Caballo negro
			if (isPointInsideSphere(camara->getPoint(), caballoNegro->getSphere(5.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Caballo carreta
			if (isPointInsideSphere(camara->getPoint(), carreta->getSphere(8.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Barrel
			if (isPointInsideSphere(camara->getPoint(), barrel->getSphere(5.0f))) {
				camara->posCam = camara->pastPosCam;
			}

			//Bala1
			if (isPointInsideSphere(camara->getPoint(), bala1->getSphere(10))) {

				if (balas >= 0 && balas <= 4 && !ocultarBala1)
				{
					ocultarBala1 = true;
					balas += 1;
				}
			}

			//Bala2
			if (isPointInsideSphere(camara->getPoint(), bala2->getSphere(10))) {

				if (balas >= 0 && balas <= 4 && !ocultarBala2)
				{
					ocultarBala2 = true;
					balas += 1;
				}
			}

			//Bala3
			if (isPointInsideSphere(camara->getPoint(), bala3->getSphere(10))) {

				if (balas >= 0 && balas <= 4 && !ocultarBala3)
				{
					ocultarBala3 = true;
					balas += 1;
				}
			}

			//Bala4
			if (isPointInsideSphere(camara->getPoint(), bala4->getSphere(10))) {

				if (balas >= 0 && balas <= 4 && !ocultarBala4)
				{
					ocultarBala4 = true;
					balas += 1;
				}
			}

			//Bala5
			if (isPointInsideSphere(camara->getPoint(), bala5->getSphere(10))) {

				if (balas >= 0 && balas <= 4 && !ocultarBala5)
				{
					ocultarBala5 = true;
					balas += 1;
				}
			}

			////Vaquero
			//if (isPointInsideSphere(camara->getPoint(), enemigo1->getSphere(6))) {
			//	camara->posCam = camara->pastPosCam;
			//}

			/*---------------------------------------------------------------------------*/
			/*                                                 MODELOS                                                 */
			/*---------------------------------------------------------------------------*/

			cantina->Draw(camara->vista, camara->proyeccion, terreno->Superficie(55, -90), camara->posCam, 10.0f, 0, 'A', 1, true, false);
			molino->Draw(camara->vista, camara->proyeccion, terreno->Superficie(77, 106), camara->posCam, 10.0f, 0, 'A', 1, true, false);
			tronco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			tronco1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			tronco2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			vagon->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, -40) - 3, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			caballoNegro->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-100, -99), camara->posCam, 10.0f, 0, 'A', 1, true, false);
			caballoBlanco->setPosX(camara->hdveo.x);
			caballoBlanco->setPosZ(camara->hdveo.z);
			caballoBlanco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(caballoBlanco->getPosX(), caballoBlanco->getPosZ()), camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 1, this->setCamaraTipo, true);

			if (!ocultarBala1)
				bala1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala1->getPosX(), bala1->getPosZ()) + elevacionModelo, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala2)
				bala2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala2->getPosX(), bala2->getPosZ()) + elevacionModelo, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala3)
				bala3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala3->getPosX(), bala3->getPosZ()) + elevacionModelo, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala4)
				bala4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala4->getPosX(), bala4->getPosZ()) + elevacionModelo, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala5)
				bala5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala5->getPosX(), bala5->getPosZ()) + elevacionModelo, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			carreta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(80, 15), camara->posCam, 10.0f, 0, 'A', 1, true, false);
			carril->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-40, 10) + 1, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			barrel->Draw(camara->vista, camara->proyeccion, terreno->Superficie(34, 30), camara->posCam, 10.0f, 0, 'A', 1, true, false);
			if (!movEnemigo1Dir)
				enemigo1->setPosX(enemigo1->getPosX() + movEnemigo1X);
			if (movEnemigo1Dir)
				enemigo1->setPosX(enemigo1->getPosX() - movEnemigo1X);

			enemigo1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(enemigo1->getPosX(), enemigo1->getPosZ()) + 1, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			//bala->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala->getPosX(), bala->getPosZ()) + 1, camara->posCam, 10.0f, 0, 'A', 1, true, false);
			//pistola->Draw(camara->vista, camara->proyeccion, terreno->Superficie(pistola->getPosX(), pistola->getPosZ()) + 2, camara->posCam, 10.0f, 2.0f, 'Y', 1, true, false);
		}
		else {
			/*---------------------------------------------------------------------------*/
			/*                                                 Billboards  tercera                                     */
			/*---------------------------------------------------------------------------*/
				/*ARBOLES*/
			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				20, -83, terreno->Superficie(20, -83) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				100, -85, terreno->Superficie(100, -85) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-100, -60, terreno->Superficie(-100, -60) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-30, 40, terreno->Superficie(-30, 40) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				50, 90, terreno->Superficie(50, 90) - 1, 18, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbol->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				90, 0, terreno->Superficie(90, 0) - 1, 15, uv1, uv2, uv3, uv4, frameBillboard, false);


			/*ARBUSTOS*/
			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				20, 0, terreno->Superficie(20, 0) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				80, 30, terreno->Superficie(80, 30) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				100, -40, terreno->Superficie(100, -40) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-40, -60, terreno->Superficie(-40, -60) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-40, 100, terreno->Superficie(-40, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-80, 80, terreno->Superficie(-80, 80) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				-80, 100, terreno->Superficie(-80, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);

			billArbusto->Draw(camara->vista, camara->proyeccion, camara->posCam3P,
				80, 100, terreno->Superficie(-80, 100) - 1.8, 3.5, uv1, uv2, uv3, uv4, frameBillboard, false);
			/*-------------------------------------------------------------------------------*/
			/*                                                  COLISIONES TERCERA                                  */
			/*-------------------------------------------------------------------------------*/
			//Cantina
			if (isPointInsideSphere(caballoBlanco->getPoint(0), cantina->getSphere(40.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Molino
			if (isPointInsideSphere(caballoBlanco->getPoint(0), molino->getSphere(25.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Carreta
			if (isPointInsideSphere(caballoBlanco->getPoint(0), tronco1->getSphere(25.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Caballo negro
			if (isPointInsideSphere(caballoBlanco->getPoint(0), caballoNegro->getSphere(10.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Caballo carreta
			if (isPointInsideSphere(caballoBlanco->getPoint(0), carreta->getSphere(22.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Barrel
			if (isPointInsideSphere(caballoBlanco->getPoint(0), barrel->getSphere(15.0f))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Bala1
			if (isPointInsideSphere(camara->getPoint(), bala1->getSphere(10))) {

				if (balas >= 0 && balas < 4 && !ocultarBala1)
				{
					ocultarBala1 = true;;
					balas += 1;
					balasList.push_back(bala);
				}
			}

			//Bala2
			if (isPointInsideSphere(camara->getPoint(), bala2->getSphere(10))) {

				if (balas >= 0 && balas < 4 && !ocultarBala2)
				{
					ocultarBala2 = true;;
					balas += 1;
					balasList.push_back(bala);
				}
			}

			//Bala3
			if (isPointInsideSphere(camara->getPoint(), bala3->getSphere(10))) {

				if (balas >= 0 && balas < 4 && !ocultarBala3)
				{
					ocultarBala3 = true;;
					balas += 1;
					balasList.push_back(bala);
				}
			}

			//Bala4
			if (isPointInsideSphere(camara->getPoint(), bala4->getSphere(10))) {

				if (balas >= 0 && balas < 4 && !ocultarBala4)
				{
					ocultarBala4 = true;;
					balas += 1;
					balasList.push_back(bala);
				}
			}

			//Bala5
			if (isPointInsideSphere(camara->getPoint(), bala5->getSphere(10))) {

				if (balas >= 0 && balas < 4 && !ocultarBala5)
				{
					ocultarBala5 = true;
					balas += 1;
					balasList.push_back(bala);
				}
			}

			//Enemigo
			if (isPointInsideSphere(caballoBlanco->getPoint(0), enemigo1->getSphere(15))) {
				camara->posCam3P = camara->pastPosCam;
			}

			//Enemigo1
			if (isPointInsideSphere(bala->getPointBala(), enemigo1->getSphere(15))) {
				ocultarEnemigo1 = true;
			}

			/*-------------------------------------------------------------------------------------------------------*/
			/*                                                                  Modelos tercera persona                                                     */
			/*-------------------------------------------------------------------------------------------------------*/
			cantina->Draw(camara->vista, camara->proyeccion, terreno->Superficie(55, -90), camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			molino->Draw(camara->vista, camara->proyeccion, terreno->Superficie(77, 106), camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			tronco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			tronco1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			tronco2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, 40) + 4, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			vagon->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-55, -40) - 3, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			caballoNegro->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-100, -99), camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			caballoBlanco->setPosX(camara->hdveo.x);
			caballoBlanco->setPosZ(camara->hdveo.z);
			caballoBlanco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(caballoBlanco->getPosX(), caballoBlanco->getPosZ()), camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 1, this->setCamaraTipo, true);

			if (!ocultarBala1)
				bala1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala1->getPosX(), bala1->getPosZ()) + elevacionModelo, camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala2)
				bala2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala2->getPosX(), bala2->getPosZ()) + elevacionModelo, camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala3)
				bala3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala3->getPosX(), bala3->getPosZ()) + elevacionModelo, camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala4)
				bala4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala4->getPosX(), bala4->getPosZ()) + elevacionModelo, camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			if (!ocultarBala5)
				bala5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(bala5->getPosX(), bala5->getPosZ()) + elevacionModelo, camara->posCam3P, 10.0f, rotCam + XM_PI, 'Y', 2, true, false);

			carreta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(80, 15), camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			carril->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-40, 10) + 1, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			//barrel->Draw(camara->vista, camara->proyeccion, terreno->Superficie(34, 30), camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			if (!ocultarEnemigo1) {
				if (!movEnemigo1Dir)
					enemigo1->setPosX(enemigo1->getPosX() + movEnemigo1X);
				if (movEnemigo1Dir)
					enemigo1->setPosX(enemigo1->getPosX() - movEnemigo1X);
				enemigo1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(enemigo1->getPosX(), enemigo1->getPosZ()) + 1, camara->posCam3P, 10.0f, 0, 'A', 1, true, false);
			}

			if (!movBalabool)
			{
				bala->setPosX(camara->hdveo.x);
				bala->setPosZ(camara->hdveo.z);
				bala->Draw(camara->vista, camara->proyeccion, camara->hdveo.y, camara->posCam3P, 10.0f, rotCam + XM_PI, -(rotCamX - XM_PIDIV2), 1, this->setCamaraTipo, true);
				rotxAux = rotCamX;
				rotyAux = rotCam;
				xbalaAux = camara->hdveo.x;
				zbalaAux = camara->hdveo.z;
				ybalaAux = camara->hdveo.y;
			}
			else
			{
				movBala += 1.5f;
				bala->setPosX(xbalaAux);
				bala->setPosZDisparo(zbalaAux + movBala);
				bala->Disparo(camara->vista, camara->proyeccion, ybalaAux, camara->posCam3P, 10.0f, rotyAux + XM_PI, 1);
			}
		}
		/*if (playGame)
			segundos -= 0.2;*/
		std::string tiempo = texto->Time(segundos);

		stringstream txtbala;
		txtbala << balas;

		string numBalas = txtbala.str();

		if (vidas == 3)
			fullVida->Draw(-0.8, 0.9);
		if (vidas == 2)
			middleVida->Draw(-0.8, 0.9);
		if (vidas == 1)
			endVida->Draw(-0.8, 0.9);
		if (vidas == 0 || tiempo == "0:00")
		{
			playGame = false;;
			gameOver->Draw(0, 0);
		}

		if (balas == 4)
			balasFull->Draw(0.85, -0.85);
		if (balas == 3)
			balas3->Draw(0.85, -0.85);
		if (balas == 2)
			balas2->Draw(0.85, -0.85);
		if (balas == 1)
			balas1->Draw(0.85, -0.85);
		if (balas == 0)
			balasEmpty->Draw(0.85, -0.85);

		cruz->Draw(0, 0);

		texto->DrawText(0.3, 0.95, "Tiempo de juego restante: " + tiempo, 0.010f);
		textoBalas->DrawText(-0.3, 0.95, "Cantidad de balas: " + numBalas, 0.010f);
		playRevolver = false;
		swapChain->Present(1, 0);
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2])
			collition = true;
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable = true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);

		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable = true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}
};
#endif