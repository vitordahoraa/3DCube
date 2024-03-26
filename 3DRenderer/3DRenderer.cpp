#include <iostream>
#include <GL/freeglut.h>
#include <vector>
using vertice = std::pair<double, double>;
using vertice3D = std::vector<double>;
using lista_vertices = std::vector<vertice>;
using lista_vertices3D = std::vector<vertice3D>;
using aresta = std::pair<int, int>;
using lista_arestas = std::vector<aresta>;
using lista_lados = std::vector<lista_arestas>;
using cor = std::vector<float>;
using cores = std::vector<cor>;

//first = eixo X
//second = eixo Y

struct Poligono {
	double tamanhoLado;
	int numLados;
	vertice posicao;
	vertice escala;
	double rotacao;
	lista_vertices vertices;
	lista_arestas arestas;
};

struct Poligono3D {
	double offset;
	int numLados;
	int numArestasPorLado;
	vertice3D posicao;
	vertice3D escala;
	double rotacao;
	lista_vertices3D vertices;
	lista_lados lados;
};

Poligono criar_poligono(double posicao_x, double posicao_y, double tamanho_lado, int num_lados);
Poligono3D criar_cubo(double posicao_x, double posicao_y, double posicao_z, double offset_initPos);
void desenhar(Poligono poligono);
void desenhar3D(Poligono3D poligono);
void movimentar(Poligono& poligono, double distancia, double angulo);
void movimentar3D(Poligono3D& poligono, double distancia, int direcao);
void escalar(Poligono& poligono, double escala_x, double escala_y);
void escalar3D(Poligono3D& poligono, double escala_x, double escala_y, double escala_z);
void rotacionar(Poligono& poligono, double angulo);
void rotacionar3D(Poligono3D& poligono, double angulo_x, double angulo_y, double angulo_z);
void display();
void display3D();
void redraw(int value);
void redraw3D(int value);
void keyboard(unsigned char key, int x, int y);
void keyboard3D(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void keyboard_special3D(int key, int x, int y);
void initGL();
void reshape(GLsizei width, GLsizei height);

Poligono pentagono;
Poligono3D cubo;
int delay = 10;
/*
int main(int argc, char** argv) {

	pentagono = criar_poligono(128, 128, 100, 5);
	glutInit(&argc, argv);

	glutInitWindowSize(512, 512);

	glutCreateWindow("Poligonos");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutTimerFunc(10, redraw, 0);

	glutMainLoop();

	return 0;
}
*/
int main(int argc, char** argv) {

	cubo = criar_cubo(1.5f, 0, -7.0f, 1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Double buffer
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("3D Cube");

	glutDisplayFunc(display3D);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard3D);
	glutSpecialFunc(keyboard_special3D);

	glutTimerFunc(10, redraw3D, 0);
	
	initGL();
	glutMainLoop();
	
	return 0;
}


void display3D(void) {
	// PARA DENHAR POLIGONO 2D
	//glClear(GL_COLOR_BUFFER_BIT);
	//desenhar(pentagono);
	//glFlush();
	// PARA DESENHAR POLIGONO3D
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
	glMatrixMode(GL_MODELVIEW);     //Operar na matriz de ModelView

	// Renderiza um cubo com 6 quads diferentes
	glLoadIdentity();                 // Reseta para a matriz identidade
	//glTranslatef(1.5f, 0.0f, -7.0f);  // Move para a direta da view o que será desenhado


	desenhar3D(cubo);

	glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando
}
void display(void) {


//	PARA DENHAR POLIGONO 2D
	glClear(GL_COLOR_BUFFER_BIT);
	desenhar(pentagono);
	glFlush();
}
void keyboard(unsigned char key, int x, int y) {
	std::cout << key;
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'z':
		escalar(pentagono, 1.1, 1.1);
		break;
	case 'x':
		escalar(pentagono, 0.9, 0.9);
		break;
	}
}

void keyboard3D(unsigned char key, int x, int y) {
	std::cout << key;
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'z':
		escalar3D(cubo, 1.1, 1.1,1.1);
		break;
	case 'x':
		escalar3D(cubo, 0.9, 0.9,0.9);
		break;
	case 'e':
		movimentar3D(cubo, 0.1, 5);
		break;
	case 'q':
		movimentar3D(cubo, 0.1, 6);
		break;
	}
}

void keyboard_special(int key, int x, int y) {
	std::cout << key;
	switch (key) {
	case GLUT_KEY_DOWN:
		movimentar(pentagono, 10, (270 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_UP:
		movimentar(pentagono, 10, (90 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_RIGHT:
		movimentar(pentagono, 10, (0 / 180.0) * 3.1416);
		break;

	case GLUT_KEY_LEFT:
		movimentar(pentagono, 10, (180 / 180.0) * 3.1416);
		break;

	}
}



void keyboard_special3D(int key, int x, int y) {
	std::cout << key;
	switch (key) {
	case GLUT_KEY_DOWN:
		movimentar3D(cubo, 0.1, 1);
		break;

	case GLUT_KEY_UP:
		movimentar3D(cubo, 0.1, 2);
		break;

	case GLUT_KEY_RIGHT:
		movimentar3D(cubo, 0.1, 3);
		break;

	case GLUT_KEY_LEFT:
		movimentar3D(cubo, 0.1, 4);
		break;

	}
}

void redraw(int value) {
	rotacionar(pentagono, 0.01);
	glutPostRedisplay();
	glutTimerFunc(delay, redraw, 0);
}

void redraw3D(int value) {
	rotacionar3D(cubo, 0.01, 0.01, 0.01);
	glutPostRedisplay();
	glutTimerFunc(delay, redraw3D, 0);
}

Poligono criar_poligono(double posicao_x, double posicao_y, double tamanho_lado, int num_lados) {
	Poligono novo_poligono;
	novo_poligono.numLados = num_lados;
	novo_poligono.posicao.first = posicao_x;
	novo_poligono.posicao.second = posicao_y;
	novo_poligono.tamanhoLado = tamanho_lado;

	novo_poligono.escala.first = 1;
	novo_poligono.escala.second = 1;

	novo_poligono.rotacao = 0;

	float angulo = 0;
	float passo_angulo = ((360 / float(num_lados)) * 3.1415926536) / 180.0;

	float apothem = tamanho_lado / (2 * tan(3.1416 / float(num_lados)));
	posicao_x -= tamanho_lado / 2.0;
	posicao_y -= apothem;

	novo_poligono.vertices.push_back(vertice(posicao_x, posicao_y));
	std::cout << "Vertices:\n";
	std::cout << 0 << " - " << posicao_x << " - " << posicao_y << "\n";
	for (int i = 1; i < num_lados; i++) {
		posicao_x = posicao_x + tamanho_lado * cos(angulo);
		posicao_y = posicao_y + tamanho_lado * sin(angulo);
		novo_poligono.vertices.push_back(vertice(posicao_x, posicao_y));
		std::cout << i << " - " << posicao_x << " - " << posicao_y << "\n";
		angulo += passo_angulo;
	}

	std::cout << "Arestas:\n";
	for (int i = 0; i < num_lados; i++) {
		novo_poligono.arestas.push_back(aresta(i, (i + 1) % num_lados));
		std::cout << i << " - " << (i + 1) % num_lados << "\n";
	}


	return novo_poligono;
}

Poligono3D criar_cubo(double posicao_x, double posicao_y, double posicao_z, double offset_initPos){
	Poligono3D novo_poligono;
	novo_poligono.numLados = 6;
	novo_poligono.numArestasPorLado = 4;
	novo_poligono.posicao.push_back(posicao_x);
	novo_poligono.posicao.push_back(posicao_y);
	novo_poligono.posicao.push_back(posicao_z);
	novo_poligono.offset = offset_initPos;

	novo_poligono.escala.push_back(1);
	novo_poligono.escala.push_back(1);
	novo_poligono.escala.push_back(1);

	novo_poligono.rotacao = 0;

	std::cout << "Vertices:\n";

	double posicao_x_insert, posicao_y_insert, posicao_z_insert = 0;
	// Lado da frente
	posicao_x_insert = posicao_x - offset_initPos;
	posicao_y_insert = posicao_y + offset_initPos;
	posicao_z_insert = posicao_z + offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 0 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x + offset_initPos;
	posicao_y_insert = posicao_y + offset_initPos;
	posicao_z_insert = posicao_z + offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 1 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x + offset_initPos;
	posicao_y_insert = posicao_y - offset_initPos;
	posicao_z_insert = posicao_z + offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 2 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x - offset_initPos;
	posicao_y_insert = posicao_y - offset_initPos;
	posicao_z_insert = posicao_z + offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 3 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";

	// Lado de trás
	posicao_x_insert = posicao_x - offset_initPos;
	posicao_y_insert = posicao_y + offset_initPos;
	posicao_z_insert = posicao_z - offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 4 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x + offset_initPos;
	posicao_y_insert = posicao_y + offset_initPos;
	posicao_z_insert = posicao_z - offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 5 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x + offset_initPos;
	posicao_y_insert = posicao_y - offset_initPos;
	posicao_z_insert = posicao_z - offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 6 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	posicao_x_insert = posicao_x - offset_initPos;
	posicao_y_insert = posicao_y - offset_initPos;
	posicao_z_insert = posicao_z - offset_initPos;

	novo_poligono.vertices.push_back(vertice3D{ posicao_x_insert, posicao_y_insert, posicao_z_insert });
	std::cout << 7 << " - " << posicao_x_insert << " - " << posicao_y_insert << " - " << posicao_z_insert << "\n";


	int aresta_de, aresta_ate = 0;

	lista_arestas lado_frente, lado_tras,lado_esquerdo,lado_direito,lado_cima,lado_baixo;

	std::cout << "Arestas:\n";

	//FRENTE
	aresta_de = 0;
	aresta_ate = 1;
	lado_frente.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 1;
	aresta_ate = 2;
	lado_frente.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 2;
	aresta_ate = 3;
	lado_frente.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 3;
	aresta_ate = 0;
	lado_frente.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_frente);

	//CIMA
	aresta_de = 0;
	aresta_ate = 4;
	lado_cima.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 4;
	aresta_ate = 5;
	lado_cima.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 5;
	aresta_ate = 1;
	lado_cima.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 1;
	aresta_ate = 0;
	lado_cima.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_cima);

	//TRAS
	aresta_de = 4;
	aresta_ate = 5;
	lado_tras.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 5;
	aresta_ate = 6;
	lado_tras.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 6;
	aresta_ate = 7;
	lado_tras.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 7;
	aresta_ate = 4;
	lado_tras.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_tras);

	//BAIXO
	aresta_de = 3;
	aresta_ate = 2;
	lado_baixo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 2;
	aresta_ate = 6;
	lado_baixo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 6;
	aresta_ate = 7;
	lado_baixo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 7;
	aresta_ate = 3;
	lado_baixo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_baixo);

	//ESQUERDO
	aresta_de = 0;
	aresta_ate = 3;
	lado_esquerdo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 3;
	aresta_ate = 7;
	lado_esquerdo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 7;
	aresta_ate = 4;
	lado_esquerdo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 4;
	aresta_ate = 0;
	lado_esquerdo.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_esquerdo);

	//DIREITO
	aresta_de = 1;
	aresta_ate = 2;
	lado_direito.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 2;
	aresta_ate = 6;
	lado_direito.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 6;
	aresta_ate = 5;
	lado_direito.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	aresta_de = 5;
	aresta_ate = 1;
	lado_direito.push_back(aresta(aresta_de, aresta_ate));
	std::cout << aresta_de << " - " << aresta_ate << "\n";

	novo_poligono.lados.push_back(lado_direito);


	return novo_poligono;
}

void movimentar(Poligono& poligono, double distancia, double angulo) {
	poligono.posicao.first = poligono.posicao.first + distancia * cos(angulo);
	poligono.posicao.second = poligono.posicao.second + distancia * sin(angulo);

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].first = poligono.vertices[i].first + distancia * cos(angulo);
		poligono.vertices[i].second = poligono.vertices[i].second + distancia * sin(angulo);
	}
}


void movimentar3D(Poligono3D& poligono, double distancia, int direcao) {

	switch (direcao) {
	case 1:
		poligono.posicao[0] = poligono.posicao[0];
		poligono.posicao[1] = poligono.posicao[1] - distancia;
		poligono.posicao[2] = poligono.posicao[2];

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0];
			poligono.vertices[i][1] = poligono.vertices[i][1] - distancia;
			poligono.vertices[i][2] = poligono.vertices[i][2];
		}
		break;

	case 2:
		poligono.posicao[0] = poligono.posicao[0];
		poligono.posicao[1] = poligono.posicao[1] + distancia;
		poligono.posicao[2] = poligono.posicao[2];

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0];
			poligono.vertices[i][1] = poligono.vertices[i][1] + distancia;
			poligono.vertices[i][2] = poligono.vertices[i][2];
		}
		break;
	case 3:
		poligono.posicao[0] = poligono.posicao[0] + distancia;
		poligono.posicao[1] = poligono.posicao[1];
		poligono.posicao[2] = poligono.posicao[2];

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0] + distancia;
			poligono.vertices[i][1] = poligono.vertices[i][1];
			poligono.vertices[i][2] = poligono.vertices[i][2];
		}
		break;
	case 4:
		poligono.posicao[0] = poligono.posicao[0] - distancia;
		poligono.posicao[1] = poligono.posicao[1];
		poligono.posicao[2] = poligono.posicao[2];

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0] - distancia;
			poligono.vertices[i][1] = poligono.vertices[i][1];
			poligono.vertices[i][2] = poligono.vertices[i][2];
		}
		break;
	case 5:
		poligono.posicao[0] = poligono.posicao[0];
		poligono.posicao[1] = poligono.posicao[1];
		poligono.posicao[2] = poligono.posicao[2] + distancia;

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0];
			poligono.vertices[i][1] = poligono.vertices[i][1];
			poligono.vertices[i][2] = poligono.vertices[i][2] + distancia;
		}
		break;
	case 6:
		poligono.posicao[0] = poligono.posicao[0];
		poligono.posicao[1] = poligono.posicao[1];
		poligono.posicao[2] = poligono.posicao[2] - distancia;

		for (int i = 0; i < poligono.vertices.size(); i++) {
			poligono.vertices[i][0] = poligono.vertices[i][0];
			poligono.vertices[i][1] = poligono.vertices[i][1];
			poligono.vertices[i][2] = poligono.vertices[i][2] - distancia;
		}
		break;
	}
}

void escalar(Poligono& poligono, double escala_x, double escala_y) {
	poligono.escala.first = poligono.escala.first * escala_x;
	poligono.escala.second = poligono.escala.second * escala_y;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].first = poligono.vertices[i].first - poligono.posicao.first;
		poligono.vertices[i].second = poligono.vertices[i].second - poligono.posicao.second;

		poligono.vertices[i].first = poligono.vertices[i].first * escala_x;
		poligono.vertices[i].second = poligono.vertices[i].second * escala_y;

		poligono.vertices[i].first = poligono.vertices[i].first + poligono.posicao.first;
		poligono.vertices[i].second = poligono.vertices[i].second + poligono.posicao.second;
	}
}


void escalar3D(Poligono3D& poligono, double escala_x, double escala_y, double escala_z) {
	poligono.escala[0]= poligono.escala[0] * escala_x;
	poligono.escala[1] = poligono.escala[1] * escala_y;
	poligono.escala[2] = poligono.escala[2] * escala_z;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i][0] = poligono.vertices[i][0] - poligono.posicao[0];
		poligono.vertices[i][1] = poligono.vertices[i][1] - poligono.posicao[1];
		poligono.vertices[i][2] = poligono.vertices[i][2] - poligono.posicao[2];

		poligono.vertices[i][0] = poligono.vertices[i][0] * escala_x;
		poligono.vertices[i][1] = poligono.vertices[i][1] * escala_y;
		poligono.vertices[i][2] = poligono.vertices[i][2] * escala_z;

		poligono.vertices[i][0] = poligono.vertices[i][0] + poligono.posicao[0];
		poligono.vertices[i][1] = poligono.vertices[i][1] + poligono.posicao[1];
		poligono.vertices[i][2] = poligono.vertices[i][2] + poligono.posicao[2];
	}
}

void rotacionar(Poligono& poligono, double angulo) {
	//X’ = X * cos ɵ - Y * sin ɵ;
	//Y’ = X * sin ɵ + Y * cos ɵ;
	poligono.rotacao = poligono.rotacao + angulo;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i].first = poligono.vertices[i].first - poligono.posicao.first;
		poligono.vertices[i].second = poligono.vertices[i].second - poligono.posicao.second;

		double x = poligono.vertices[i].first;
		double y = poligono.vertices[i].second;

		poligono.vertices[i].first = x * cos(angulo) - y * sin(angulo);

		poligono.vertices[i].second = x * sin(angulo) + y * cos(angulo);

		poligono.vertices[i].first = poligono.vertices[i].first + poligono.posicao.first;
		poligono.vertices[i].second = poligono.vertices[i].second + poligono.posicao.second;
	}

}
void rotacionar3D(Poligono3D& poligono, double angulo_x, double angulo_y, double angulo_z) {
	//X’ = X +  * cos ɵ - Y * sin ɵ;
	//Y’ = X * sin ɵ + Y * cos ɵ;
	//Z’ = X * sin ɵ + Y * cos ɵ;
	poligono.rotacao = poligono.rotacao + angulo_x;

	for (int i = 0; i < poligono.vertices.size(); i++) {
		poligono.vertices[i][0] = poligono.vertices[i][0] - poligono.posicao[0];
		poligono.vertices[i][1] = poligono.vertices[i][1] - poligono.posicao[1];
		poligono.vertices[i][2] = poligono.vertices[i][2] - poligono.posicao[2];

		double x = poligono.vertices[i][0];
		double y = poligono.vertices[i][1];
		double z = poligono.vertices[i][2];

		poligono.vertices[i][0] = x * cos(angulo_y) * cos(angulo_z) + y * (sin(angulo_x) * sin(angulo_y) * cos(angulo_z) - cos(angulo_x) * sin(angulo_z)) + z * (cos(angulo_x) * sin(angulo_y) * cos(angulo_z) + sin(angulo_x) * sin(angulo_z));
		poligono.vertices[i][1] = x * cos(angulo_y) * sin(angulo_z) + y * (sin(angulo_x) * sin(angulo_y) * sin(angulo_z) + cos(angulo_x) * cos(angulo_z)) + z * (cos(angulo_x) * sin(angulo_y) * sin(angulo_z) - sin(angulo_x) * cos(angulo_z));
		poligono.vertices[i][2] = x * -sin(angulo_y) * cos(angulo_z) + y * (sin(angulo_x) * cos(angulo_y)) +	z * (cos(angulo_x) * cos(angulo_y));

		poligono.vertices[i][0] = poligono.vertices[i][0] + poligono.posicao[0];
		poligono.vertices[i][1] = poligono.vertices[i][1] + poligono.posicao[1];
		poligono.vertices[i][2] = poligono.vertices[i][2] + poligono.posicao[2];
	}

}

void desenhar(Poligono poligono) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < poligono.arestas.size(); i++) {
		float v_o = poligono.arestas[i].first;
		float v_d = poligono.arestas[i].second;
		glVertex2f(poligono.vertices[v_o].first, poligono.vertices[v_o].second);
		glVertex2f(poligono.vertices[v_d].first, poligono.vertices[v_d].second);
	}
	glEnd();
}

void desenhar3D (Poligono3D poligono) {

	cor Verde = { 0.0f, 1.0f,0.0f };
	cor Laranja = { 0.0f,0.5f,0.0f };
	cor Vermelho = { 1.0f,0.0f,0.0f };
	cor Amarelo= { 1.0f,1.0f,0.0f };
	cor Azul = { 0.0f,0.0f,1.0f };
	cor Magenta = { 1.0f,0.0f,1.0f };

	cores Cores = { Verde, Laranja, Vermelho, Amarelo, Azul, Magenta };

	glBegin(GL_QUADS);
	for (int lado = 0; lado < poligono.lados.size(); lado++) {
		

		glColor3f(Cores[lado][0], Cores[lado][1], Cores[lado][2]); 
		for (int aresta = 0; aresta < poligono.lados[lado].size(); aresta++) {

			float v_o = poligono.lados[lado][aresta].first;
			float v_d = poligono.lados[lado][aresta].second;

			glVertex3f(poligono.vertices[v_o][0], poligono.vertices[v_o][1], poligono.vertices[v_o][2]);
			glVertex3f(poligono.vertices[v_d][0], poligono.vertices[v_d][1], poligono.vertices[v_d][2]);

		}
	}

	glEnd();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Coloca a cor de background para preto e opaco
	glClearDepth(1.0f);                   // Define o buffer de profundidade para o mais distante possível
	glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
	glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade
}
