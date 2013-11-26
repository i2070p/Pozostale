// Deklaracje funkcji używanych jako obsługa zdarzeń GLUT-a.
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
// Uniwersalna struktura reprezentująca trójwymiarowy wektor.
// Może służyć do przechowywania pozycji, wektora, itp. Wskazane jest rozszerzenie
// tej struktury o metody i operatory pozwalające na wykonywanie operacji na 
// wektorach - to na pewno się przyda.

float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
float angleX = 0.0f;
float angleY = 0.0f;
struct vec3 {
	float x, y, z;
};

// Struktura pozwalająca na przechowanie aktualnego stanu kamery.
struct SCameraState {
	vec3 pos; // pozycja kamery
	vec3 dir; // kierunek patrzenia (wektor jednostkowy)
	float speed; // mnożnik zmian pozycji - "szybkość" ruchów kamery
};

// Zmianna przechowująca aktualny stan kamery.
SCameraState player;
