#include "stdafx.h"
#include "FallingBoxesApplication.h"

#define Z_PLANE 0.0f

FallingBoxesApplication::FallingBoxesApplication()
{
}

FallingBoxesApplication::FallingBoxesApplication(ProjectionType projectionType):BulletOpenGLApplication(projectionType) 
{
}

void FallingBoxesApplication::InitializePhysics() {

	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);

	// Adding for 2D collisions and solving
	m_pDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, new btBox2dBox2dCollisionAlgorithm::CreateFunc());

	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	Create2DBoxes();
}

/* Override inputs */

void FallingBoxesApplication::Mouse(int button, int state, int x, int y) {
	switch (state)
	{

	case GLUT_UP:
		break;
	case GLUT_DOWN:

		switch (button)
		{

		case GLUT_LEFT_BUTTON:
		{
			//printf("screen width = %f, screen height = %f\n", m_screenWidth, m_screenHeight);
			printf("Position of mouse click = (%d, %d)\n", x, y);
			float x_position = (float)(x - (int)(m_screenWidth / 2));
			float y_position = (float)(-y + (int)(m_screenHeight / 2));
			printf("Position relative to center = (%f,%f)\n", x_position, y_position);
			float object_cam_distance = abs(Z_PLANE - m_cameraManager->GetCameraLocation().getZ());
			printf("object to cam distance = %f\n", object_cam_distance);
			float x_meters = x_position * GetPixelsToMeters(object_cam_distance);
			float y_meters = y_position * GetPixelsToMeters(object_cam_distance);
			printf("x meters, y meters = (%f, %f)\n", x_meters, y_meters);
			btVector3 halfSize(2, 2, 0);
			btVector3 position(x_meters, y_meters, Z_PLANE);
			//printf("(x,y) = (%f,%f)\n", x_meters, y_meters);
			//btVector3 position(0, 20, 10.0f);
			btVector3 color(((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX));
			
			CreateBox(halfSize, 5, color, position);
		}
			break;

		default:
			break;
		}

		break;
	default:
		break;
	}
}


void FallingBoxesApplication::ShutdownPhysics() {
	
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;

}

void FallingBoxesApplication::Create2DBoxes() {
	printf("Create some boxes \n");
	// Create a ground box
	btVector3 halfSize(2, 25, 0);
	btVector3 position(0, -5, Z_PLANE);
	CreateBox(halfSize, 0, btVector3(0.1f, 0.3f, 0.8f), position);

	// Crate a dynamic box
	btVector3 halfSize1(2, 2, 0);
	btVector3 position1(5, 20, Z_PLANE);
	btVector3 color1(((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX));
	//CreateBox(halfSize1, 5, color1, position1);
}

void FallingBoxesApplication::CreateBox(const btVector3 &halfSize, float mass, const btVector3 &color, const btVector3 &position) {

	GameObject *aBox = CreateGameObject(new btBox2dShape(halfSize), mass, color, position);
}


FallingBoxesApplication::~FallingBoxesApplication()
{
}