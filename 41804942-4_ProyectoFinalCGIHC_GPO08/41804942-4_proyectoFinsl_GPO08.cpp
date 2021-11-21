// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;








//VENTILADOR
float rotfan= 0.0f;//rotar el ventilador
bool fanrot;//activa la animación del ventilador
//GATO
bool catmov;//para que se active al presionar una tecla
float movcatx = 0.0f;//movimineto del gato en el eje x
float movcatz = 0.0f;//movimineto en el eje z
float rotcat = 90.0f;//rotar al gato, esto en el eje y
//recorridos gato son ciclicos
bool recocat1 = true;//son cuatro estados del movimineto del gato sobre el sofa
bool recocat2 = false;
bool recocat3 = false;
bool recocat4 = false;
//RATA
bool ratmov;//movimineto del ratón cuando se presone una tecla, en este caso será la R
float rotrat = 315.0f;//rotación de la rata en el eje y 
float rotrat2 = 0.0f;// rotación de la rata en el eje x, 
float movratx = 0.0f;
float movraty = 0.0f;//para subir o bajar de la mesa
float movratz = 0.0f;
//recorrido rata es ciclico
bool recorat1 = true;// el total de recorridos hacia la pizza, aqui en diaganoal en el piso
bool recorat2 = false;//sube por la mesa
bool recorat3 = false;//llega a la pizza
bool recorat4 = false;//regresa al borde de la mesa
bool recorat5 = false;//baja de la mesa
bool recorat6 = false;//regresa a su posición oringinal

//PERRO
bool dogmov;//activar animación del perro con la tecla P
float rotdog = 0.0f;//rota para la parte del salto
float rotdog2 = 0.0f;//rota para regresar por el mismo camino hacia la posiscion original (1)
float dogmovx = 0.0f;//recorre pasto
float dogmovy = 0.0f;//salto y caida
//recorrido perro
bool recodog1 = true;
bool recodog2 = false;//salta
bool recodog3 = false;//cae
bool recodog4 = false;
bool recodog5 = false;//regresa
bool recodog6 = false;//salta
bool recodog7 = false;//cae
bool recodog8 = false;


//PAJARO
bool movpaja;//animacion vuelo con presionar una tecla, será B
float rotpaja = 0.0f;//para volar en diagonal
float movpajx = 0.0f;//despalaza en x
float movpajz = 0.0f;// desplaza en z
//recorrido pajaro
bool recopaj1=true;
bool recopaj2=false;//diagonal
bool recopaj3=false;
bool recopaj4=false;//diagonal

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto CGIHC García Lazcano", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    
    // Carga de modelos
    Model casa((char*)"Models/casa/casa.obj");
    Model piso((char*)"Models/piso/piso.obj");
    Model gato((char*)"Models/cat/gato.obj");
    Model arbol((char*)"Models/arbol/arbol.obj");
    Model basura((char*)"Models/basura/basura.obj");
    Model mesa((char*)"Models/mesa/mesa.obj");
    Model pizzza((char*)"Models/pizzza/pizzza.obj");
    Model Librero((char*)"Models/librero/librero.obj");
    Model carpet((char*)"Models/alfo/carpet.obj");
    Model pasto((char*)"Models/pasto/pasto.obj");
    Model buro((char*)"Models/buro/buro.obj");
    Model tv((char*)"Models/tv/tv.obj");
    Model fan((char*)"Models/fan/fan.obj");
    Model beu((char*)"Models/beu/beu.obj");
    Model lampa((char*)"Models/lamp/lampa.obj");
    Model coach((char*)"Models/coach/coach.obj");
    Model dog((char*)"Models/dog/dogo.obj");
    Model rat((char*)"Models/rat/rat.obj");
    Model van((char*)"Models/van/van.obj");
    Model bird((char*)"Models/bird/bird.obj");
    Model radio((char*)"Models/radio/radio.obj");
    Model silla((char*)"Models/silla/silla.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Dibujando los modelos cargados
        //CASA
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.32f, 0.0f));        
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE,glm::value_ptr(model));        
        casa.Draw(shader);
        //PISO
        model = glm::mat4(1);//setea la matriz
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.7f));//redimensiona el piso, puesto que invade las escaleras
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        piso.Draw(shader);//dibuja el modelo
        //GATO
        model = glm::mat4 (1);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//gato algo grande, se opto por reducirlo aquí
        model = glm::translate(model, glm::vec3(0.3f + movcatx, 1.95f, -3.0f+ movcatz));//posisción original más los moviminetos de los estados
        model = glm::rotate(model, glm::radians(rotcat), glm::vec3(0.0f, 1.0f, 0.0f));//cse rota cuando se necesita en la animación
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        gato.Draw(shader);
        //ARBOL
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.0f, -0.32f, 6.0f));
         glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE,glm::value_ptr(model));
        arbol.Draw(shader);
        //BASURA
        model = glm::mat4 (1);
        model = glm::translate(model, glm::vec3(6.4f, -0.32f, 3.8f));//queda fuera de la casa
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        basura.Draw(shader);
        //MESA
        model = glm::mat4 (1);
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));//muy pequeña en su objeto original, se decidio hacerla un poco más grande
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));//girada para parecer como en la imagen sugerida
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesa.Draw(shader);
        //PIZZA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 0.5725f, 1.5f));//será la comida de la rata
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pizzza.Draw(shader);
        //BURÓ
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.75f, 0.1f, 3.8f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f, 0.5f, 0.75f));//demasiado grande al ser exportado
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        buro.Draw(shader);
        //television
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.75f, 0.78f, 3.75f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));// cuando se rota la imagen de la tele se distyorciona, no pude reparalo
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tv.Draw(shader);
        //LIBRERO 01
        model = glm::mat4 (1);
        model = glm::translate(model, glm::vec3(5.9f, 0.0f, -2.85f));
        model = glm::rotate(model, glm::radians(90.0f),glm::vec3(0.0f,-1.0f,0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Librero.Draw(shader);
        //LIBRERO02
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, -3.9f));        
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Librero.Draw(shader);
        //LIBRERO03
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, -3.9f));        
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Librero.Draw(shader);
        //ALFOMBRA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        carpet.Draw(shader);
        //ventilador
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 3.9f, 0.0f));
        model = glm::rotate(model, glm::radians(-rotfan), glm::vec3(0.0f, 1.0f, 0.0f));//gira como uno normal, con la tecla q
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fan.Draw(shader);
        //buro02
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));//demasiado grande, se necesito redimensionar
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        beu.Draw(shader);
        //LAMPARA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 0.5f, -1.0f));
        model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));//muy grande, se redimensiono
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lampa.Draw(shader);
        //SILLON
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.0f, -0.1f, -1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        coach.Draw(shader);
        //pasto
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.32f, 0.0f));//su puso más abajo, debido a que la casa cuenta con un nivel más arriba, y era más
        //caótico mover todo que simplemente mover los pisos y la casa
        model = glm::scale(model, glm::vec3(4.0f, 1.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pasto.Draw(shader);
        //PERRO
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(18.0f+dogmovx, -0.32f+dogmovy, 12.0f));//recorrido del perro
        model = glm::rotate(model, glm::radians(rotdog), glm::vec3(0.0f, 0.0f, 1.0f));//rotación que simula el salto
        model = glm::rotate(model, glm::radians(rotdog2), glm::vec3(0.0f, 1.0f, 0.0f));//rotación que simula el regreso al estado 1
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);
        //VAN
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.32f, 12.0f));//la saltará el perro
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        van.Draw(shader);
        //RATA
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));//muy grande, se redimensiono para ser más estetica
        model = glm::translate(model, glm::vec3(3.5f + movratx, 0.05f + movraty, -1.5f + movratz));//simula el movimineto
        model = glm::rotate(model, glm::radians(rotrat), glm::vec3(0.0f, 1.0f, 0.0f));//orientación de la dirección d ela rata en los ejes x & z
        model = glm::rotate(model, glm::radians(rotrat2), glm::vec3(1.0f, 0.0f, 0.0f));// orientación al escalar, esto en el eje y
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        rat.Draw(shader);
        //radio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.275f, 2.35f, -3.55f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        radio.Draw(shader);
        //SILLA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);
        //PAJARO
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f + movpajx, 8.0f, -12.0f + movpajz));// animación del vuelo
        model = glm::rotate(model, glm::radians(rotpaja), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bird.Draw(shader);
        glBindVertexArray(0);
        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
  //MOVIMINETO VENTILADOR
    if (fanrot) {        
        rotfan += 0.1f;
    }
    else if (!fanrot) {
        rotfan += 0.0f;
    }
    //MOVIMINETO GATO
    if (catmov) {
        if (recocat1) {
            if (movcatx > 4.44f ) {
                recocat1 = false;
                recocat2 = true;
                rotcat = 0.0f;
            }
            else {
                movcatx+=0.005f;
            }
        }        
        if (recocat2) {
            if (movcatz > 4.49) {
                recocat2 = false;
                recocat3 = true;
                rotcat = 180.0f;
            }
            else {
                movcatz += 0.005f;
            }
        }        
        if (recocat3) {
            if (movcatz < 0.01) {
                recocat3 = false;
                recocat2 = false;
                recocat4 = true;
                rotcat = 270;
            }
            else {
                movcatz -= 0.005f;
            }

        }        
        if (recocat4) {
            if (movcatx < 0.00) {
                recocat4 = false;
                recocat1 = true;
                rotcat = 90.0f;
            }
            else {
                movcatx -= 0.005f;
            }
        }

    }



    //moviminetos de la rata
    if (ratmov) {
        if (recorat1) {
            if (movratx < -3.5f && movratz >3.3f) {
                recorat1 = false;//termina estado 1
                recorat2 = true;//inincia estado 2
                rotrat = 0.0f;
                rotrat2 = 270.0f;//orientación para que suba la  rata por la mesa
            }
            else {
                movratx -= 0.005f;//se mueve en x
                movratz += 0.0049f;// se mueve en z
            }
        }
        if (recorat2) {
            if (movraty > 0.7) {
                recorat2 = false;
                recorat3 = true;
                rotrat = 270.0f;// se dirige a  la pizza
                rotrat2 = 0.0f;//vuelve a la posisción del piso
            }
            else {
                movraty += 0.0005f;//sube por la mesa, velocidad lenta para apreciar el movimineto
            }
        }
        if (recorat3) {
            if (movratx < -4.0f) {
                recorat3 = false;                
                recorat4 = true;
                rotrat = 90.0;//orienta a regreso por donde vino
            }
            else {
                movratx -= 0.0005f;//va a la pizza
            }

        }
        if (recorat4) {
            if (movratx > -3.5f) {
                recorat4 = false;
                recorat5 = true;
                rotrat = 180.0f;//sentido para que no colicione con la pata de la mesa
                rotrat2 = 90.0f;//mira hacia abajo
            }
            else {
                movratx += 0.0005f;//regresa a la orilla de la mesa
            }
        }
        if (recorat5) {
            if (movraty < 0.01) {
                recorat5 = false;
                recorat6 = true;
                rotrat = 135.0f;//mira hacia posisción 1
                rotrat2 = 0.0f;// posiscion a raz de suelo
            }
            else {
                movraty -= 0.0005f;//baja la mesa
            }
        }
        if (recorat6) {
            if (movratx > 0.00 && movratz < 0.0f) {
                recorat6 = false;
                recorat1 = true;
                rotrat = 315.0f;//mira de nuevo hacia la mesa
            }
            else {
                movratx += 0.005f;//regresa ala posición original
                movratz -= 0.0049;
            }
        }
    }


    //recorrido perro
    if (dogmov) {
        if (recodog1) {
            if (dogmovx < -15.0f) {
                recodog1 = false;
                recodog2 = true;
                rotdog = -45.0f;//ángulo de salto
                rotdog2 = 0.0f;
            }
            else {
                dogmovx -= 0.0075f;                
            }
        }
        if (recodog2) {
            if (dogmovx < -18.0f && dogmovy>1.5f) {//simula salto, arriba y enfrente
                recodog2 = false;
                recodog3 = true;
                rotdog = 45.0f;//ángulo para aterrizar
                rotdog2 = 0.0f;//ve hacia el destino
            }
            else {
                dogmovx -= 0.0075f;//dirección
                dogmovy += 0.00375;//salto
            }
        }
        if (recodog3) {
            if (dogmovx < -21.0f && dogmovy <0.01) {//simula salto, abajo y enfrente
                recodog3 = false;                
                recodog4 = true;
                rotdog = 0.0f;
                rotdog2 = 0.0f;
            }
            else {
                dogmovx -= 0.0075f;
                dogmovy -= 0.00375;
            }

        }
        if (recodog4) {
            if (dogmovx < -36.0f) {
                recodog4 = false;
                recodog5 = true;
                rotdog = 0.0f;
                rotdog2 = 180.0f;// ve hacia la posisción original
            }
            else {
                dogmovx -= 0.0075f;
            }
        }
        if (recodog5) {
            if (dogmovx > -21.0f) {
                recodog5 = false;
                recodog6 = true;
                rotdog = 45.0f;//ángulo de salto
                rotdog2 = 180.0f;
            }
            else {
                dogmovx += 0.0075f;
            }
        }
        if (recodog6) {//salto número 2 parte 1
            if (dogmovx > -18.0f && dogmovy > 1.5f) {
                recodog6 = false;
                recodog7 = true;
                rotdog = -45.0f;//ángulo para aterrizar
                rotdog2 = 180.0f;
            }
            else {
                dogmovx += 0.0075f;
                dogmovy += 0.00375;
            }

        }
        if (recodog7) {//salto  número 2, parte 2  , aterrizaje
            if (dogmovx > -15.0f && dogmovy < 0.0f) {
                recodog7 = false;
                recodog8 = true;
                rotdog = 0.0f;
                rotdog2 = 180.0f;
            }
            else {
                dogmovx += 0.0075f;
                dogmovy -= 0.00375;
            }

        }
        if (recodog8) {
            if (dogmovx > 0.0f) {
                recodog8 = false;
                recodog1 = true;
                rotdog = 0.0f;
                rotdog2 = 0.0f;// ve hacia el destino
            }
            else {
                dogmovx += 0.0075f;
            }
        }
    }

    //RECORRIDO PAJARO
    if (movpaja) {//se activa con la tecla B
        if (recopaj1) {//vuelta en z, ess decir, de frente
            if (movpajz > 24.0f) {
                recopaj1 = false;
                recopaj2 = true;
                rotpaja = 135.0f;//voltea a la dirección del estado 2
            }
            else {
                movpajz += 0.01f;
            }
        }
        if (recopaj2) {
            if (movpajx > 24.0f && movpajz < 0.0f) {//vuelo diagonal
                recopaj2 = false;
                recopaj3 = true;
                rotpaja = 0.0f;//voltea a ver de frente para vuelo
            }
            else {
                movpajz -= 0.01f;//vuelo en diagonal, parte del eje x
                movpajx += 0.01f;//vuelo en diagonal, parte del eje z
            }
        }
        if (recopaj3) {
            if (movpajz > 24.0f) {
                recopaj3 = false;                
                recopaj4 = true;
                rotpaja = 225.0f;//mira a la posisción del estado 1
            }
            else {
                movpajz += 0.01f;//vuela de frente, o en z
            }

        }
        if (recopaj4) {
            if (movpajx < 0.0f && movpajz < 0.0f) {
                recopaj4 = false;
                recopaj1 = true;
                rotpaja = 0.0f;//vuelo para el estado 1
            }
            else {
                movpajx -= 0.01f;//vuela al inicio
                movpajz -= 0.01f;
            }
        }

    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
    if (keys[GLFW_KEY_O]) {
        rot += 0.2;
    }
    if (keys[GLFW_KEY_Q]) {//se activa el ventilador
        fanrot=!fanrot;
    }
    if (keys[GLFW_KEY_E]) {// se activa el movimineto del gato
        catmov = !catmov;
    }
    if (keys[GLFW_KEY_R]) {//Movimiento de la rata
        ratmov = !ratmov;
    }
    if (keys[GLFW_KEY_P]) {//Movimineto del perro
        dogmov = !dogmov;
    }
    if (keys[GLFW_KEY_B]) {//vuelo del pajaro
        movpaja = !movpaja;
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}
/*García Lazcano Carlos D.
UNAM, CU, FI, 2022-1
Computación Gráfica e Interacción Humano Computadora*/
