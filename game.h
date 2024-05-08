#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "graphics.h"
#include <cmath>
struct Player
{
    int x, y;
    int dx, dy;
    float speed;

       void move1(const Uint8* keys, Player& otherPlayer)
    {
        int newX = x;
        int newY = y;

        if (keys[SDL_SCANCODE_W] && y - speed >= FIELD_Y - 30)
            newY -= speed;
        if (keys[SDL_SCANCODE_S] && y + speed <= FIELD_Y + FIELD_HEIGHT + 30)
            newY += speed;
        if (keys[SDL_SCANCODE_A] && x - speed >= FIELD_X - 30)
            newX -= speed;
        if (keys[SDL_SCANCODE_D] && x + speed <= FIELD_X + FIELD_WIDTH + 30)
            newX += speed;

// Kiểm tra va chạm goal1
    bool hitGoal1 = false;
    if (newX - PLAYER_RADIUS < FIELD_X + GOAL_WIDTH &&
        newX + PLAYER_RADIUS > FIELD_X  &&
        newY - PLAYER_RADIUS < FIELD_Y + GOAL_Y + GOAL_HEIGHT &&
        newY + PLAYER_RADIUS > FIELD_Y + GOAL_Y)
    {
        hitGoal1 = true;
    }

    // Kiểm tra va chạm goal2
    bool hitGoal2 = false;
    if (newX - PLAYER_RADIUS < FIELD_X + FIELD_WIDTH  &&
        newX + PLAYER_RADIUS > FIELD_X + FIELD_WIDTH - GOAL_WIDTH &&
        newY - PLAYER_RADIUS < FIELD_Y + GOAL_Y + GOAL_HEIGHT &&
        newY + PLAYER_RADIUS > FIELD_Y + GOAL_Y)
    {
        hitGoal2 = true;
    }
        int dx = newX - otherPlayer.x;
        int dy = newY - otherPlayer.y;
        int distance = std::sqrt(dx * dx + dy * dy);


    if (distance >= PLAYER_RADIUS * 2 &&!hitGoal1 && !hitGoal2)
    {
        x = newX;
        y = newY;
    }

    }

    void move2(const Uint8* keys, Player& otherPlayer)
        {
            int newX = x;
            int newY = y;

            if (keys[SDL_SCANCODE_UP] && y - speed >= FIELD_Y - 30)
                newY -= speed;
            if (keys[SDL_SCANCODE_DOWN] && y + speed <= FIELD_Y + FIELD_HEIGHT  + 30)
                newY += speed;
            if (keys[SDL_SCANCODE_LEFT] && x - speed >= FIELD_X - 30)
                newX -= speed;
            if (keys[SDL_SCANCODE_RIGHT] && x + speed <= FIELD_X + FIELD_WIDTH  + 30)
                newX += speed;

            int dx = newX - otherPlayer.x;
            int dy = newY - otherPlayer.y;
            int distance = std::sqrt(dx * dx + dy * dy);

           // Kiểm tra va chạm với khung thành goal1
        bool hitGoal1 = false;
        if (newX - PLAYER_RADIUS < FIELD_X + GOAL_WIDTH &&
            newX + PLAYER_RADIUS > FIELD_X  &&
            newY - PLAYER_RADIUS < FIELD_Y + GOAL_Y + GOAL_HEIGHT &&
            newY + PLAYER_RADIUS > FIELD_Y + GOAL_Y)
        {
            hitGoal1 = true;
        }

        // Kiểm tra va chạm với khung thành goal2
        bool hitGoal2 = false;
        if (newX - PLAYER_RADIUS < FIELD_X + FIELD_WIDTH  &&
            newX + PLAYER_RADIUS > FIELD_X + FIELD_WIDTH - GOAL_WIDTH &
            newY - PLAYER_RADIUS < FIELD_Y + GOAL_Y + GOAL_HEIGHT &&
            newY + PLAYER_RADIUS > FIELD_Y + GOAL_Y)
        {
            hitGoal2 = true;
        }
        if (distance >= PLAYER_RADIUS * 2 &&!hitGoal1 && !hitGoal2)
        {
            x = newX;
            y = newY;
        }

        }


        bool checkCollision(Player& ball)
        {
            int dx = x - ball.x;
            int dy = y - ball.y;
            int distance = std::sqrt(dx * dx + dy * dy);

            if (distance < PLAYER_RADIUS * 2)
            {
                ball.speed = 4;
                return true;
            }
            return false;
        }


    };

    struct logic{
        void moveBall(Player& ball)
        {
            int newX = ball.x + ball.dx * ball.speed;
            int newY = ball.y + ball.dy * ball.speed;

            if (newX - PLAYER_RADIUS < FIELD_X || newX + PLAYER_RADIUS > FIELD_X + FIELD_WIDTH)
                ball.dx *= -1;
            else
                ball.x = newX;

            if (newY - PLAYER_RADIUS < FIELD_Y || newY + PLAYER_RADIUS > FIELD_Y + FIELD_HEIGHT)
                ball.dy *= -1;
            else
                ball.y = newY;

            ball.speed *= 0.95;

            if (ball.speed < 0.08)
                ball.speed = 0;
        }
        bool checkGoal(SDL_Rect& goal, Player& ball)
        {
            if (ball.x - PLAYER_RADIUS < goal.x + goal.w &&
                ball.x + PLAYER_RADIUS > goal.x &&
                ball.y - PLAYER_RADIUS < goal.y + goal.h &&
                ball.y + PLAYER_RADIUS > goal.y)
            {
                return true;
            }
            return false;
        }
        void resetGame(Player& player1, Player& player2, Player& ball)
        {
            ball.x = 598;
            ball.y = 350;
            ball.dx = 0;
            ball.dy = 0;
            player1.x = 228;
            player1.y = 355;
            player2.x = 965;
            player2.y = 355;
        }

    };


    #endif // GAME_H_INCLUDED
