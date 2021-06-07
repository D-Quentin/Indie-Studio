/*
** EPITECH PROJECT, 2021
** indie
** File description:
** main
*/

#include "Map.hpp"

map::map()
{
}

map::~map()
{
}

std::pair<int, int> find_sym(int c, std::vector<std::vector<int>> map)
{
    std::pair<int, int> pai;
    for(int i = 0; i != map.size(); i++) {
        for(int b = 0; b != map[i].size(); b++) {
            if (map[i][b] == c) {
                pai.first = i;
                pai.second = b;
                return pai;
            }
        }
    }
    return pai;
}

void map::create_map()
{
    int ran = 0;
    this->plan_int[(this->nb_player * 10) / 2][(this->nb_player * 10) / 2] = 1;
    std::pair<int, int> pai;
    
    std::srand(std::time(nullptr));
    for (int i = 0, number = 1; number != (this->nb_player * 6); i++) {
        ran = 1 + std::rand()/((RAND_MAX + 1u)/number);
        pai = find_sym(ran, this->plan_int);
        ran = std::rand()/((RAND_MAX + 0u)/4);
        if (ran == 0 && this->plan_int[pai.first - 1][pai.second] == 0) {
            number++;
            this->plan_int[pai.first - 1][pai.second] = number;
        }
        else if (ran == 1 && this->plan_int[pai.first][pai.second + 1] == 0) {
            number++;
            this->plan_int[pai.first][pai.second + 1] = number;
        }
        else if (ran == 2 && this->plan_int[pai.first + 1][pai.second] == 0) {
            number++;
            this->plan_int[pai.first + 1][pai.second] = number;
        }
        else if (ran == 3 && this->plan_int[pai.first][pai.second - 1] == 0) {
            number++;
            this->plan_int[pai.first][pai.second - 1] = number;
        }
    }
}

void map::create_L_room(int number, int x, int y) 
{
    if (this->plan_int[x - 1][y] > 0 && this->plan_int[x - 1][y - 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x - 1][y] = number, this->plan_int[x - 1][y - 1] = number;
    else if (this->plan_int[x - 1][y] > 0 && this->plan_int[x - 1][y + 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x - 1][y] = number, this->plan_int[x - 1][y + 1] = number;
    else if (this->plan_int[x + 1][y] > 0 && this->plan_int[x + 1][y - 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x + 1][y] = number, this->plan_int[x + 1][y - 1] = number;
    else if (this->plan_int[x + 1][y] > 0 && this->plan_int[x + 1][y + 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x + 1][y] = number, this->plan_int[x + 1][y + 1] = number;
    else if (this->plan_int[x][y + 1] > 0 && this->plan_int[x + 1][y + 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x][y + 1] = number, this->plan_int[x + 1][y + 1] = number;
    else if (this->plan_int[x][y + 1] > 0 && this->plan_int[x - 1][y + 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x][y + 1] = number, this->plan_int[x - 1][y + 1] = number;
    else if (this->plan_int[x][y - 1] > 0 && this->plan_int[x + 1][y - 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x][y - 1] = number, this->plan_int[x + 1][y - 1] = number;
    else if (this->plan_int[x][y - 1] > 0 && this->plan_int[x - 1][y - 1] > 0)
        this->plan_int[x][y] = number, this->plan_int[x][y - 1] = number, this->plan_int[x - 1][y - 1] = number;
}

void map::create_I_room(int number, int x, int y) 
{
    if (this->plan_int[x + 1][y] > 0) 
        this->plan_int[x][y] = number, this->plan_int[x + 1][y] = number;
    else if (this->plan_int[x - 1][y] > 0) 
        this->plan_int[x][y] = number, this->plan_int[x - 1][y] = number;
    else if (this->plan_int[x][y + 1] > 0) 
        this->plan_int[x][y] = number, this->plan_int[x][y + 1] = number;
    else if (this->plan_int[x][y - 1] > 0) 
        this->plan_int[x][y] = number, this->plan_int[x][y - 1] = number;
}


void map::create_rooms()
{
    std::pair<int, int> pos;
    int number = 0;
    int ran = 0;

    for (int i = 1; i != (this->nb_player * 6) + 1; i++) {
        pos = find_sym(i, this->plan_int);
        while (pos.first != 0 && pos.second != 0) {
            if (this->plan_int[pos.first + 1][pos.second] <= 0 && this->plan_int[pos.first - 1][pos.second] <= 0 
            && this->plan_int[pos.first][pos.second + 1] <= 0 && this->plan_int[pos.first][pos.second - 1] <= 0) {
                number = number - 1;
                this->plan_int[pos.first][pos.second] = number;
            } else {
                ran = 1 + std::rand()/((RAND_MAX + 1u)/4) - 1;
                if (ran == 0)
                    create_L_room(number - 1, pos.first,pos.second);
                if (ran == 1)
                    create_I_room(number - 1, pos.first,pos.second);
                if (ran == 2)
                    this->plan_int[pos.first][pos.second] = (number -1);
            }
            pos = find_sym(i, this->plan_int);
        }
        number = number - 1;
    }
}

int check_vec_spawn(std::vector<int> vec, int x)
{
    for(int i = 0; i != vec.size(); i++) {
        if (vec[i] == x)
            return 1;
    }
    return 0;
}

void map::take_largest_value()
{
    this->cut_high = 0;
    this->cut_down = 0;
    this->cut_left = RAND_MAX;
    this->cut_right = 0;

    for (int i = 0; i != this->plan_int.size(); i++)
        for (int b = 0; b != this->plan_int[i].size(); b++)
            if (this->plan_int[i][b] != 0 && this->cut_high == 0)
                this->cut_high = i;
    for (int i = (this->cut_high + 1), c = 0; i != this->plan_int.size(); i++) {
        for (int b = 0; b != this->plan_int[i].size(); b++) {
            c = c + this->plan_int[i][b];
        }
        if (c == 0 && this->cut_down == 0)
            this->cut_down = i;
        c = 0;
    }
    for (int i = 0; i != this->plan_int.size(); i++)
        for (int b = 0; b != this->plan_int[i].size(); b++)
            if (this->plan_int[i][b] != 0 && b < this->cut_left)
                this->cut_left = b;
    for (int i = 0; i != this->plan_int.size(); i++)
        for (int b = this->plan_int[i].size() - 1; b != 0; b--)
            if (this->plan_int[i][b] != 0 && b > this->cut_right)
                this->cut_right = b;
}

void map::create_empty_square()
{
    for(int k = 0; k != (this->size*11); k++)
        this->char_list_high.push_back('E');
    for(int k = 0; k != (this->size*11); k++)
        this->char_list.push_back('E');
    for(int k = 0; k != (this->size*11); k++)
        this->char_list_down.push_back('E');
    for(int k = 0; k != (this->size*11); k++)
        this->char_list_mid.push_back('E');
}

void map::create_high_square_part(int i, int j)
{
    if (i != this->cut_high && this->plan_int[i][j] == this->plan_int[i - 1][j]) {
        for(int k = 0; k != this->size; k++)
            this->char_list_high.push_back('X');
        for(int k = 0; k != this->size * 9; k++)
            this->char_list_high.push_back(' ');
        for(int k = 0; k != this->size; k++)
            this->char_list_high.push_back('X');
    }
    else if (i != (this->cut_high) && this->plan_int[i][j] != this->plan_int[i - 1][j] && this->plan_int[i - 1][j] != 0) {
        for(int k = 0; k != (this->size * 5); k++)
            this->char_list_high.push_back('X');
        for(int k = 0; k != this->size; k++)
            this->char_list_high.push_back('H');
        for(int k = 0; k != this->size * 5; k++)
            this->char_list_high.push_back('X');
    }
    else {
        for(int k = 0; k != this->size * 11; k++)
            this->char_list_high.push_back('X');
    }
}

void map::create_mid_square_part(int i, int j)
{
    if (j != cut_left && this->plan_int[i][j] != this->plan_int[i][j - 1] && this->plan_int[i][j - 1] != 0) {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back('H');
    } else if (j != cut_left && this->plan_int[i][j] == this->plan_int[i][j - 1]) {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back(' ');
    }
    else {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back('X');
    }
    for(int k = 0; k != this->size * 4; k++)
        char_list_mid.push_back(' ');
    if (check_vec_spawn(this->vec_spawn, this->plan_int[i][j]) == 0) {
        char_list_mid.push_back('S');
        for(int k = 0; k != this->size - 1; k++)
            char_list_mid.push_back(' ');  
        this->vec_spawn.push_back(this->plan_int[i][j]);
    } else {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back(' ');
    }
    for(int k = 0; k != this->size * 4; k++)
        char_list_mid.push_back(' ');
    if (j != cut_right && this->plan_int[i][j] != this->plan_int[i][j + 1] && this->plan_int[i][j + 1] != 0) {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back('H');
    } else if (j != cut_right && this->plan_int[i][j] == this->plan_int[i][j + 1]) {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back(' ');
    }
    else {
        for(int k = 0; k != this->size; k++)
            char_list_mid.push_back('X');
    }
}

void map::create_square_part(int i, int j)
{
    if (j != cut_left && this->plan_int[i][j] == this->plan_int[i][j - 1])
        for(int k = 0; k != this->size; k++)
            char_list.push_back(' ');
    else 
        for(int k = 0; k != this->size; k++)
            char_list.push_back('X');
    for(int k = 0; k != this->size * 9; k++)
        char_list.push_back(' ');
    if (j != cut_right && this->plan_int[i][j] == this->plan_int[i][j + 1])
        for(int k = 0; k != this->size; k++)
            char_list.push_back(' ');
    else 
        for(int k = 0; k != this->size; k++)
            char_list.push_back('X');
}

void map::create_down_square_part(int i, int j)
{
    if (i != cut_down && this->plan_int[i][j] == this->plan_int[i + 1][j]) {
        for(int k = 0; k != this->size; k++)
            char_list_down.push_back('X');
        for(int k = 0; k != this->size * 9; k++)
            char_list_down.push_back(' ');
        for(int k = 0; k != this->size; k++)
            char_list_down.push_back('X');
    }
    else if (this->plan_int[i][j] != this->plan_int[i + 1][j] && this->plan_int[i + 1][j] != 0) {
        for(int k = 0; k != this->size * 5; k++)
            char_list_down.push_back('X');
        for(int k = 0; k != this->size; k++)
            char_list_down.push_back('H');
        for(int k = 0; k != this->size * 5; k++)
            char_list_down.push_back('X');
    }
    else
        for(int k = 0; k != this->size * 11; k++)
            char_list_down.push_back('X'); 
}

std::vector<char> map::remove_spawn_point(std::vector<char> str)
{
    for(int i = 0; i != str.size(); i++) {
        if (str[i] == 'S')
            str[i] = ' ';
    }
    return str;
}

void map::create_real_map() 
{
    take_largest_value();

    for (int i = cut_high; i != cut_down; i++)
    {
        for(int j = cut_left; j != cut_right + 1; j++) {
            if (this->plan_int[i][j] == 0)
                create_empty_square();
            else {
                create_high_square_part(i, j);
                create_mid_square_part(i, j);
                create_square_part(i, j);
                create_down_square_part(i, j);
            }
        }
        for(int k = 0; k != this->size; k++)
            this->plan_char.push_back(char_list_high);
        for(int k = 0; k != this->size * 4; k++)
            this->plan_char.push_back(char_list);
        this->plan_char.push_back(char_list_mid);
        for(int k = 0; k != this->size - 1; k++) {
            this->plan_char.push_back(remove_spawn_point(char_list_mid));
        }
        for(int k = 0; k != this->size * 4; k++)
            this->plan_char.push_back(char_list);
        for(int k = 0; k != this->size; k++)
            this->plan_char.push_back(char_list_down);
        char_list.clear();
        char_list_down.clear();
        char_list_high.clear();
        char_list_mid.clear();
    }
}

void map::create_spawn()
{
    int ran1 = 0;
    int h = 0;
    for (int i = 0; i != this->plan_int.size(); i++) {
        for (int b = 0; b != this->plan_int[i].size(); b++) {
            if (this->plan_int[i][b] < 0) {
                for (int j = 0; j != this->vec_spawn.size(); j++) {
                    if (this->vec_spawn[j] == this->plan_int[i][b]) {
                        h++;
                    }
                }
                if (h == 0)
                    this->vec_spawn.push_back(this->plan_int[i][b]);
            }
            h = 0;
        }
    }
    for (int i = 0; i != nb_player; i++) {
        ran1 = 1 + std::rand()/((RAND_MAX + 1u)/this->vec_spawn.size());
        this->vec_spawn.erase((this->vec_spawn.begin() + ran1) - 1);
    }
}

std::vector<std::vector<char>> map::create(int nb_player, int size)
{
    std::vector<int> map_int;

    this->nb_player = nb_player;
    this->size = size;
    for(int i = 0; i != ((this->nb_player * 20) * (this->nb_player * 20)) - 1; i++) {
        map_int.push_back(0);
        if (map_int.size() % (this->nb_player * 20) == 0) {
            this->plan_int.push_back(map_int);
            map_int.clear();
        }
    }
    create_map();
    create_rooms();
    create_spawn();
    create_real_map();
    return this->plan_char;
}

std::vector<std::vector<char>> setup_door(std::vector<std::vector<char>> map, int nb, int i, int size)
{
    int o = 0;
    int p = 0;

    printf("%d\n", size);
    for (; i != 0 && map[nb-1][i] != 'X' && map[nb+4][i] != 'X'; i--);
    p = i;
    i++;
    for (;map[nb-1][i+1] != 'X' && map[nb+4][i+1] != 'X'; i++, o++);
    int rando = rand()%o +1;
    for (int m = 0; m != size*2; m++) {
        for(int c = 0; c != size; c++)
            map[nb-m+((size*2)-1)][p+rando+c] = ' ';
    }
    return (map);
}

std::vector<std::vector<char>> setup2_door(std::vector<std::vector<char>> map, int nb, int i, int size)
{
    int o = 0;
    int p = 0;
    int c = i;

    for (; i != 0 && map[nb][i-1] != 'X' && map[nb][i+4] != 'X'; nb--);
    p = nb;
    nb++;
    for (;map[nb][i-1] != 'X' && map[nb][i+4] != 'X'; nb++, o++);
    int rando = rand()%o -1;
    for (int m = 0; m != 2*size; m++) {
        for (int c = 0; c != size; c++) {
            map[p+rando+1+c][i+m] = ' ';
        }
    }
    return (map);
}

std::vector<std::vector<char>> check(std::vector<std::vector<char>> map, int nb, int size)
{
    for (int i = 0; i != map[nb].size(); i++) {
        if (map[nb][i] == 'H' && map[nb][i-1] == 'X' && map[nb-1][i] == ' ')
            map = setup_door(map, nb, i, size);
        if (map[nb][i] == 'H' && map[nb-1][i] == 'X' && map[nb][i-1] == ' ')
            map = setup2_door(map, nb, i, size);
    }
    return (map);
}

std::vector<std::vector<char>> change_door(std::vector<std::vector<char>> map, int size)
{
    int a = 0;

    for (int i = 0; i != map.size(); i++) {
        map = check(map, i, size);
    }
    for (int i = 0; i != map.size(); i++)
        for (int o = 0; o != map[i].size() != '\0'; o++)
            if (map[i][o] == 'H')
                map[i][o] = 'X';
    return (map);
}

std::vector<std::vector<char>> main_create_map(int nb_player, int nb_wall)
{
    map cart;

    std::vector<std::vector<char>> plan = cart.create(nb_player, nb_wall);
    plan = change_door(plan, nb_wall);
    return plan;
}