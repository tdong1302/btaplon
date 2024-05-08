#include "graphics.h"
#include "game.h"

int main(int argc, char* argv[]) {

    Graphics graphics;
    graphics.init();
    logic logic;


     TTF_Font* font = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 100);
      SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText("START", font, color);
    graphics.renderTexture(helloText, 200, 200);
        graphics.presentScene();


    TTF_Font* font1 = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 30);
    SDL_Color color1 = {255, 255, 0, 0};

    bool startGame = false;
    SDL_Event event;
    int mouseX, mouseY;
    while (!startGame) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 215 && mouseX <= 600 && mouseY >= 229 && mouseY <= 312) {
                    startGame = true;
                    Mix_PlayChannel(-1, graphics.hitSound, 0);
                }
            }
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(graphics.renderer);
                SDL_DestroyWindow(graphics.window);
                SDL_Quit();
                return 0;
            }
        }
    }

    Player player1 = {228,355, 0, 0, 4};
    Player player2 = {965,355, 0, 0, 4};
    Player ball = {598, 350, 0, 0, 2};
    SDL_Rect goal1 = {FIELD_X , FIELD_Y + GOAL_Y, GOAL_WIDTH, GOAL_HEIGHT};
    SDL_Rect goal2= {FIELD_X + FIELD_WIDTH - GOAL_WIDTH , FIELD_Y + GOAL_Y, GOAL_WIDTH, GOAL_HEIGHT};

    int player1Score = 0;
    int player2Score = 0;
    bool quit = false;

    Uint32 gameDuration = 20;
    Uint32 start = SDL_GetTicks();

    while (!quit) {
             Uint32 currentTime = SDL_GetTicks();
    if (currentTime - start >= gameDuration * 1000) {
        quit = true;
    }

        while (SDL_PollEvent(&event) != 0) {
            if (event.type  == SDL_QUIT) {
                quit = true;
            }
        }
       //SDL_GetMouseState(&mouseX, &mouseY);
       // cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << endl;
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        player1.move1(keys, player2);
        player2.move2(keys, player1);

        logic.moveBall(ball);

        if (player1.checkCollision(ball)) {
            int dx = ball.x - player1.x;
            int dy = ball.y - player1.y;
            int distance = sqrt(dx * dx + dy * dy);
            ball.dx = ball.speed * dx / distance;
            ball.dy = ball.speed * dy / distance;

             Mix_PlayChannel(-1, graphics.hitSound, 0);
        }

        if (player2.checkCollision(ball)) {
            int dx = ball.x - player2.x;
            int dy = ball.y - player2.y;
            int distance = sqrt(dx * dx + dy * dy);
            ball.dx = ball.speed * dx / distance;
            ball.dy = ball.speed * dy / distance;

             Mix_PlayChannel(-1, graphics.hitSound, 0);
        }

        if (logic.checkGoal(goal1, ball)) {
            player2Score++;
            Mix_PlayChannel(-1, graphics.goalSound, 0);
            logic.resetGame(player1, player2, ball);
        }

        if (logic.checkGoal(goal2, ball)) {
            player1Score++;
            Mix_PlayChannel(-1, graphics.goalSound, 0);
            logic.resetGame(player1, player2, ball);
        }

        SDL_RenderClear(graphics.renderer);
        SDL_SetRenderDrawColor(graphics.renderer, 0, 128, 0, 255);
        SDL_RenderFillRect(graphics.renderer, nullptr);

        SDL_Rect fieldRect = {FIELD_X, FIELD_Y, FIELD_WIDTH, FIELD_HEIGHT};
        SDL_RenderCopy(graphics.renderer, graphics.fieldTexture, nullptr, &fieldRect);

        SDL_Rect player1Rect = {player1.x - PLAYER_RADIUS, player1.y - PLAYER_RADIUS, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
        SDL_RenderCopy(graphics.renderer, graphics.playerTexture1, nullptr, &player1Rect);

        SDL_Rect player2Rect = {player2.x - PLAYER_RADIUS, player2.y - PLAYER_RADIUS, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
        SDL_RenderCopy(graphics.renderer, graphics.playerTexture2, nullptr, &player2Rect);

        SDL_Rect ballRect = {ball.x - PLAYER_RADIUS, ball.y - PLAYER_RADIUS, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
        SDL_RenderCopy(graphics.renderer, graphics.ballTexture, nullptr, &ballRect);

        SDL_RenderCopy(graphics.renderer, graphics.goalTexture, nullptr, &goal1);
        SDL_RenderCopy(graphics.renderer, graphics.goalTexture, nullptr, &goal2);


     string scoreString = "score : "+to_string(player1Score) + " - " + to_string(player2Score);
      const char* scoreCString = scoreString.c_str();
      SDL_Texture* scoreText = graphics.renderText(scoreCString, font1, color1);
      graphics.renderTexture(scoreText,738,0);

        Uint32 remainingTime = (gameDuration * 1000 - (SDL_GetTicks() - start)) / 1000;
        string timeString = "Time remaining: " + to_string(remainingTime) + " seconds";
        const char* timeCString = timeString.c_str();
        SDL_Texture* timeText = graphics.renderText(timeCString, font1, color1);
        graphics.renderTexture(timeText, 100, 0);
        graphics.presentScene();
        SDL_Delay(16);

    }
     Mix_PlayChannel(-1, graphics.goalSound, 0);
     SDL_RenderClear(graphics.renderer);
     if(player1Score==player2Score){
     SDL_Texture* background = graphics.loadTexture("assets/draw.jpg");
     SDL_RenderCopy(graphics.renderer, background, NULL, NULL);
     graphics.presentScene();
     graphics.waitUntilKeyPressed();
     } else
     if(player1Score>player2Score){
     SDL_Texture* background = graphics.loadTexture("assets/player1win.jpg");
     SDL_RenderCopy(graphics.renderer, background, NULL, NULL);
     graphics.presentScene();
     graphics.waitUntilKeyPressed();
     } else {
     SDL_Texture* background = graphics.loadTexture("assets/player2win.jpg");
     SDL_RenderCopy(graphics.renderer, background, NULL, NULL);
     graphics.presentScene();
     graphics.waitUntilKeyPressed();
     }

    graphics.quit();
    TTF_Quit();
    return 0;
}
