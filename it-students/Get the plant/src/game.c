#include <raylib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

Texture2D background;Texture2D youwon;Texture2D dialogBox; Texture2D moSprites[3];Texture2D characterSprites[8]; Texture2D explosionSprites[8];Texture2D bootSprite;Vector2 bootPosition;Vector2 moPosition;
int currentFrame;int framesCounter;int framesSpeed;int animFrame;int animCounter;bool lookingUp;bool lookingDown;bool lastMoveLeft;
bool showDialogMo; int idxText; bool dialogShown; float textTimer; bool isMoving; int letterCount; bool enterCode;
char inputText[50] = "\0"; bool dialogAlreadyShown; bool incorrectCode; bool initShutdown; bool closeWindow;
float timer; bool alreadyProcessed; Vector2 explosionPosition; 
float explosionFrameTime; float explosionTimer = 0.0f;
volatile sig_atomic_t MOshutdown; bool is_exploding; int explosionFrame;
bool YOU_WON;

const int MAX_LEN = 37;

typedef enum {
    IDLE_LEFT,
    IDLE_RIGHT,
    MOVE_LEFT,
    MOVE_RIGHT,
    LOOK_UP_LEFT,
    LOOK_UP_RIGHT,
    LOOK_DOWN_LEFT,
    LOOK_DOWN_RIGHT,
} CharacterState;

void procesar_codigo(char *buff);
void wreckage(int sig_num);

void CustomLog(int msgType, const char *text, va_list args){return;}

void cargar_texturas(void){
    Image dialogImage = LoadImage("recursos/Sprites/Dialogo.png");
    Rectangle dialogCropRect = {0,470,317,300};
    ImageCrop(&dialogImage, dialogCropRect);
    dialogBox = LoadTextureFromImage(dialogImage);
    UnloadImage(dialogImage);
    background = LoadTexture("recursos/Fondo/fondo_1.png");
    youwon = LoadTexture("recursos/Fondo/ganaste.png");
    moSprites[0] = LoadTexture("recursos/Sprites/MO_up.png");
    moSprites[1] = LoadTexture("recursos/Sprites/MO_down.png");
    moSprites[2] = LoadTexture("recursos/Sprites/MO_off.png");
    characterSprites[IDLE_LEFT] = LoadTexture("recursos/Sprites/Standing_left.png");
    characterSprites[IDLE_RIGHT] = LoadTexture("recursos/Sprites/Standing_right.png");
    characterSprites[MOVE_LEFT] = LoadTexture("recursos/Sprites/Running_left.png");
    characterSprites[MOVE_RIGHT] = LoadTexture("recursos/Sprites/Running_right.png");
    characterSprites[LOOK_UP_LEFT] = LoadTexture("recursos/Sprites/Up_left.png");
    characterSprites[LOOK_UP_RIGHT] = LoadTexture("recursos/Sprites/Up_right.png");
    characterSprites[LOOK_DOWN_LEFT] = LoadTexture("recursos/Sprites/Down_left.png");
    characterSprites[LOOK_DOWN_RIGHT] = LoadTexture("recursos/Sprites/Down_right.png");
    explosionSprites[0] = LoadTexture("recursos/Sprites/explosion/explosion1.png");
    explosionSprites[1] = LoadTexture("recursos/Sprites/explosion/explosion2.png");
    explosionSprites[2] = LoadTexture("recursos/Sprites/explosion/explosion3.png");
    explosionSprites[3] = LoadTexture("recursos/Sprites/explosion/explosion4.png");
    explosionSprites[4] = LoadTexture("recursos/Sprites/explosion/explosion5.png");
    explosionSprites[5] = LoadTexture("recursos/Sprites/explosion/explosion6.png");
    explosionSprites[6] = LoadTexture("recursos/Sprites/explosion/explosion7.png");
    explosionSprites[7] = LoadTexture("recursos/Sprites/explosion/explosion8.png");
    bootSprite = LoadTexture("recursos/Sprites/Boot.png");
    return;
}

void definir_posiciones_extras(void){
    bootPosition.x = 600.0f;
    bootPosition.y = 205.0f;
    moPosition.x = 350.0f;
    moPosition.y = 205.0f;
    explosionPosition.x = 350.0f;
    explosionPosition.y = 235.0f;
}

void definir_variables_animacion(void){
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8; // Velocidad de la animación (cuantos frames se espera antes de cambiar la imagen)
    animFrame = 0; // Para alternar entre las dos imágenes
    animCounter = 0; // Contador de tiempo    
    lookingUp = false;
    lookingDown = false;
    isMoving = false;
    lastMoveLeft = false;
    showDialogMo = false;
    dialogShown = false;
    letterCount = 0;
    enterCode = false;
    dialogAlreadyShown = false;
    incorrectCode = false;
    initShutdown = false;
    timer = 0.0f;
    closeWindow = false;
    alreadyProcessed = false;
    is_exploding = false;
    explosionFrame = 0;
    explosionFrameTime = 0.15f; 
    explosionTimer = 0.0f;
    YOU_WON = false;
    return;

}

void descargar_texturas(void){
    UnloadTexture(background);
    UnloadTexture(youwon);
    UnloadTexture(bootSprite);
    UnloadTexture(dialogBox);
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(moSprites[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        UnloadTexture(characterSprites[i]);
        UnloadTexture(explosionSprites[i]);
    }
    return;
}

void init_shutdown(void){
    timer += GetFrameTime();
    if (timer>3.0f){closeWindow = true;}
}


int main(void){
    signal(SIGSEGV, wreckage);
    SetTraceLogCallback(CustomLog);
    // Inicializa la ventana
    InitWindow(800, 400, "G3T Th3 PL4NT!");
    // Carga las texturas del sprite para las diferentes animaciones y orientaciones
    cargar_texturas();
    float scale = 1.5f;
    // Posición inicial del sprite
    Vector2 position = { 
        100 - characterSprites[IDLE_RIGHT].width / 2 * scale, 
        240 - characterSprites[IDLE_RIGHT].height / 2 * scale};
    definir_posiciones_extras();
    definir_variables_animacion();
    CharacterState state = IDLE_RIGHT;

    const char* dialogText = "ERROR 403: \nACCESO RESTRINGIDO.\nSE REQUIERE CÓDIGO DE \nAUTENTICACIÓN\n>Presiona espacio para continuar<";
    const char* downText = "\n>Presiona espacio para continuar<";
    const char* incorrectText = "ERROR. CÓDIGO INCORRECTO.\nAUTODESTRUCCIÓN EN 3,2,1...";
    // Configura la velocidad de fotogramas
    SetTargetFPS(60);

    while (!WindowShouldClose() && !closeWindow){
        if (initShutdown){init_shutdown();}
        // Estados iniciales
        lookingUp = false;
        lookingDown = false;
        isMoving = false;

        // Movimiento y actualizacion de estados
        if (!YOU_WON){
            Vector2 newPosition = position;
            if (IsKeyDown(KEY_RIGHT) && position.x < 800 - characterSprites[state].width * scale) { newPosition.x += 5.0f; state = MOVE_RIGHT; isMoving = true; lastMoveLeft = false;}
            if (IsKeyDown(KEY_LEFT) && position.x > 0) { newPosition.x -= 5.0f; state = MOVE_LEFT; isMoving = true; lastMoveLeft = true;}
            if (IsKeyDown(KEY_DOWN)) { lookingDown = true; }
            if (IsKeyDown(KEY_UP)) { lookingUp = true; }

            if (lookingUp){state = (lastMoveLeft) ? LOOK_UP_LEFT : LOOK_UP_RIGHT;}
            else if (lookingDown){state = (lastMoveLeft) ? LOOK_DOWN_LEFT : LOOK_DOWN_RIGHT;}
            else if (!isMoving){state = (lastMoveLeft) ? IDLE_LEFT : IDLE_RIGHT;}

            Rectangle characterRect = { newPosition.x, newPosition.y, characterSprites[state].width * scale, characterSprites[state].height * scale};
            Rectangle bootRect = { bootPosition.x, bootPosition.y, bootSprite.width * 0.15f, bootSprite.height * 0.15f};
            Rectangle moRect = { moPosition.x, moPosition.y, moSprites[0].width, moSprites[0].height};
            textTimer = 0.0f;
            float textSpeed = 0.1f;
            
            // Actualizar la animación solo si el personaje se está moviendo
            
            bool MO_colision = CheckCollisionRecs(characterRect,moRect) && !MOshutdown;
            YOU_WON = CheckCollisionRecs(characterRect, bootRect);

            if (!MO_colision){
                position = newPosition;
            }

            if (CheckCollisionRecs(characterRect, moRect)){
                if (!showDialogMo && !enterCode && !dialogAlreadyShown){
                    showDialogMo = true;
                }
            }
            
        
            if (dialogShown && IsKeyPressed(KEY_SPACE)){enterCode = true;showDialogMo = false;dialogAlreadyShown = true;}
            if (enterCode && !alreadyProcessed){
                int key = GetKeyPressed();
                while (key > 0){
                    if ((key >= 32) && (key <= 125) && (letterCount < 50)){
                        inputText[letterCount] = (char)key;
                        letterCount++;
                        inputText[letterCount] = '\0';
                    }
                    key = GetKeyPressed();
                    if (IsKeyPressed(KEY_SPACE) && letterCount > 1){
                        enterCode = false;
                        procesar_codigo(inputText);

                    } else if (IsKeyPressed(KEY_BACKSPACE)){
                        letterCount--;
                        if (letterCount < 0){letterCount=0;}
                        inputText[letterCount] = '\0';
                    }
                }
            }
            
            if (isMoving){framesCounter++;if (framesCounter >= (60 / framesSpeed)){framesCounter = 0;currentFrame++;if (currentFrame >= 4) currentFrame = 0;}}animCounter++;if (animCounter >= 60){animCounter = 0;animFrame = !animFrame;}
            if (is_exploding){
                if(explosionFrame==0){sleep(0.7);}
                explosionTimer += GetFrameTime();
                if (explosionTimer >= explosionFrameTime){
                    explosionFrame++;
                    if (explosionFrame >= 8){is_exploding = false;}
                explosionTimer = 0.0f;
                }
                
                
            }
        }
        
        // Inicia el dibujo
        BeginDrawing(); ClearBackground(RAYWHITE); 
        if (!YOU_WON){
            DrawTexture(background, 0, 0, WHITE);
            DrawTextureEx(bootSprite, bootPosition, 0.0f, 0.15f, WHITE);
            if(!MOshutdown){
                DrawTextureEx(moSprites[animFrame], moPosition, 0.0f, 1.2f, WHITE);
            } else {
                moPosition.y = 235.0f;
                DrawTextureEx(moSprites[2], moPosition, 0.0f, 1.2f, WHITE);
                if (is_exploding){
                    
                    DrawTextureEx(explosionSprites[explosionFrame],explosionPosition,0.0f,2.0f,WHITE);
                }
                
            }
            
            Rectangle sourceRect = { 0.0f, 0.0f, (float)characterSprites[state].width, (float)characterSprites[state].height };
            Rectangle destRect = { position.x, position.y, characterSprites[state].width * scale, characterSprites[state].height * scale };
            DrawTexturePro(characterSprites[state], sourceRect, destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

            if (showDialogMo){
                Vector2 dialogPosition = {moPosition.x, moPosition.y - dialogBox.height - 10 }; // Ajusta la posición según sea necesario
                DrawTexture(dialogBox, dialogPosition.x, dialogPosition.y, WHITE);
                if (!dialogShown){sleep(0.8); dialogShown = true;}
                DrawText(dialogText, dialogPosition.x+10, dialogPosition.y+10,13,LIGHTGRAY);   
            }
            if (enterCode){
                Vector2 dialogPosition = {position.x,position.y - 120};
                DrawTexture(dialogBox, dialogPosition.x, dialogPosition.y, WHITE);
                DrawText(inputText,dialogPosition.x+10, dialogPosition.y + 40, 12, LIGHTGRAY);
                DrawText(downText, dialogPosition.x+10, dialogPosition.y + 40, 12, LIGHTGRAY);
            }
            if (incorrectCode){
                Vector2 dialogPosition = {moPosition.x, moPosition.y - dialogBox.height - 10 }; 
                DrawTexture(dialogBox, dialogPosition.x, dialogPosition.y, WHITE);
                DrawText(incorrectText, dialogPosition.x+10, dialogPosition.y+10,13,LIGHTGRAY);
                initShutdown = true;
            }
            
        } else {
            Vector2 pos = {0,0};
            ClearBackground(BLACK);
            DrawTextureEx(youwon, pos, 0.0f,1.0f, WHITE);
        }
        
        // Termina el dibujo
        EndDrawing();
    }

    // Descarga las texturas
    descargar_texturas();

    // Cierra la ventana
    CloseWindow();

    return 0;
}

///////////////////////////////////////////////////////////////

char f1[] = "PU3_3S3T_2o24_s0Cl053Th363}"; 
char f2[] = "PU3_3S3T_2o24_n07_Y3t_0v3rR!}"; 
char f3[] = "PU3_3S3T_2o24_wr3ck1t_R4LPH}"; 
char f4[] = "PU3_3S3T_2o24_wr3cck3dd!_}"; 
char f5[] = "PU3_3S3T_2o24_wr3ck_IT_¡!"; 
char f6[] = "PU3_3S3T_2o24_n0TY3tth3r3_r4lP4}";  
char a[] = "a";
char b[] = "b";
char c[] = "c";
char d[] = "d";
char e[] = "e";
char f[] = "f";
char g[] = "g";
char h[] = "h";
char i[] = "i";


void wreckage(int sig_num) { 
    MOshutdown = 1;
    asm("nop");
    asm("nop");
    asm("nop");
    char *solucion = "Buscas algo?";
    asm("nop");
    asm("nop");
    asm("nop");
    solucion = "Espera!";
    asm("nop");
    asm("nop");
    asm("nop");
    solucion = f5;
    asm("nop");
    asm("nop");
    asm("nop");
    solucion = "Ganaste!";
    alreadyProcessed = true;
    is_exploding = true;
    return;
} 

void procesar_codigo(char *input) { 
    int len_input = (int) strlen(input);
    char tmp[MAX_LEN];
    for (int i = 0; i < len_input; i++){
        if (i > MAX_LEN){
            raise(SIGSEGV);
            return;
        } else {
            tmp[i] = input[i];
        }
    }
    char correct[10];
    if(strcmp(correct,tmp) != 1){
        incorrectCode = true;
        alreadyProcessed = true;
    }
    return;
} 