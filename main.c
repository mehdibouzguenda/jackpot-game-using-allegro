#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_ICON 8

void initialisation_allegro() {

    allegro_init();
    install_keyboard();
    install_mouse();
    enable_hardware_cursor();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 600, 0, 0) != 0) {
        // message et sortie de prog. si  echec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}

void afficher_image(BITMAP *fond, const char *filename) {


    BITMAP *image = load_bitmap(filename, NULL);
    if (!image) {
        allegro_message("Impossible de charger l'image: %s", filename);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    draw_sprite(fond, image, 3, 3); //va dessiner l'image charger
    blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre

    //destroy_bitmap(image);
}

bool menu_screen(BITMAP *fond) {
    while (1) {
        int yes_x = 200, yes_y = 250, yes_w = 100, yes_h = 50;
        int no_x = 340, no_y = 250, no_w = 100, no_h = 50;
        clear_bitmap(fond);
        textout_ex(fond, font, "Voulez-vous commencer le jeu?", 220, 220, makecol(255, 255, 255), -1);
        rectfill(fond, yes_x, yes_y, yes_x + yes_w, yes_y + yes_h, makecol(0, 255, 0));
        rectfill(fond, no_x, no_y, no_x + no_w, no_y + no_h, makecol(255, 0, 0));
        textout_ex(fond, font, "Oui", yes_x + 5, yes_y + 20, makecol(0, 0, 0), -1);
        textout_ex(fond, font, "Non", no_x + 5, no_y + 20, makecol(0, 0, 0), -1);

        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        //pour continuer le jeu il doit appuyer la flche de haut
        if (key[KEY_UP]) {
            return true;
        }
        //pour arreter le jeu appuyer sur la fleche de bas
        if (key[KEY_DOWN]) {
            return false;
        }
        //echap
        if (key[KEY_ESC]) {
            allegro_exit();
            exit(0);
        }

        rest(10);
    }
}


//enum{SYMBOLE_1 ; SYMBOLE_2; SYMBOLE_3};




int main() {


    //initialisation des variables
    BITMAP *fond = NULL;


    allegro_init();
    initialisation_allegro();

    install_keyboard();

    fond = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(fond, makecol(10, 0, 0));

    //  l'animation de démarrage
    //tableau imagine animation
    char anim[19][10] = {"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp", "6.bmp", "7.bmp", "8.bmp",
                         "9.bmp", "10.bmp", "11.bmp", "12.bmp", "13.bmp", "14.bmp", "15.bmp", "16.bmp",
                         "17.bmp", "18.bmp", "19.bmp"};
    char anim2[19][10] = {"a0.bmp", "a1.bmp", "a2.bmp", "a3.bmp", "a4.bmp", "a5.bmp", "a6.bmp", "a7.bmp"};

    //tableau image icone pour les symboles
    char icon[NUM_ICON][10] = {"icon.bmp", "icon1.bmp", "icon2.bmp", "icon3.bmp", "icon5.bmp",
                               "icon6.bmp",};

    //affichage animation
    for (int i = 0; i < 19; i++) {
        afficher_image(fond, anim[i]);
        rest(100);
    }
    afficher_image(fond, "1.bmp");
    rest(100);
    afficher_image(fond, "19.bmp");
    rest(100);
    afficher_image(fond, "1.bmp");
    afficher_image(fond, "19.bmp");
    rest(100);
    clear_bitmap(fond);
    clear_bitmap(screen);

    for (int i = 0; i < 8; i++) {
        BITMAP *img = load_bitmap(anim2[i], NULL);
        draw_sprite(fond, img, 0, 0); //va dessiner l'image charger
        blit(fond, screen, 0, 0, 0, 100, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
        //afficher_image(fond, anim2[i]);
        rest(100);
    }

    draw_sprite(fond, load_bitmap("a0.bmp", NULL), 0, 0);
    blit(fond, screen, 0, 0, 0, 100, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
    rest(200);

    draw_sprite(fond, load_bitmap("a7.bmp", NULL), 0, 0);
    blit(fond, screen, 0, 0, 0, 100, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
    rest(200);

    draw_sprite(fond, load_bitmap("a0.bmp", NULL), 0, 0);
    blit(fond, screen, 0, 0, 0, 100, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
    rest(150);

    draw_sprite(fond, load_bitmap("a7.bmp", NULL), 0, 0);
    blit(fond, screen, 0, 0, 0, 100, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
    rest(500);
    clear_bitmap(fond);

    bool game_start = false;



    //game_start = menu_screen(fond);

    //pour demarrer le jeu
    //clear_bitmap(fond);
    //clear_bitmap(screen);



    // Charger les images en dehors de la boucle

    /*  // Boucle principale
      while (!key[KEY_ESC]) {*/

    game_start = menu_screen(fond);
        if (game_start) {

            destroy_bitmap(fond);
            BITMAP *game = create_bitmap(SCREEN_W, SCREEN_H);


            BITMAP *image = NULL;

            image = load_bitmap("fond.bmp", NULL);
            if (!image) {
                allegro_message("Erreur lors du chargement de l'image.");
                return -1;
            }
            // Dessiner l'image sur l'écran
            draw_sprite(game, image, -99, 0);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            //afficher_image(fond, "fond.bmp");
            rest(10); // Limiter le taux de rafraîchissement

            //pour faire descendre la manchette
            image = load_bitmap("fond2.bmp", NULL);
            if (!image) {
                allegro_message("Erreur lors du chargement de l'image.");
                return -1;
            }
            // Dessiner l'image sur l'écran
            draw_sprite(game, image, -99, 0);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            //afficher_image(fond, "fond.bmp");
            rest(1000); // Limiter le taux de rafraîchissement


            image = load_bitmap("fond3.bmp", NULL);
            if (!image) {
                allegro_message("Erreur lors du chargement de l'image.");
                return -1;
            }
            // Dessiner l'image sur l'écran
            draw_sprite(game, image, -99, 0);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            //afficher_image(fond, "fond.bmp");
            rest(1000); // Limiter le taux de rafraîchissement

            srand(time(NULL));
            int random_index1 = 2;
            int random_index2 = 2;
            int random_index3 = 2;

            BITMAP *random_image1;
            BITMAP *random_image2;
            BITMAP *random_image3;

            //mettre la nouvelle image
            random_index1 = rand() % NUM_ICON;     //aleatoirement l index du tableau
            printf("the rand 1 = %d \n",random_index1);
            random_image1 = load_bitmap(icon[random_index1], NULL); //charger l image qui se trouve a l index du tableau
            if (!random_image1) {
                allegro_message("Impossible de charger l'image: %s", !random_image1);
                return -1;
            }
            random_index2 = rand() % NUM_ICON;
            printf("the rand 2 = %d \n",random_index2);
            random_image2 = load_bitmap(icon[random_index2], NULL);
            if (!random_image2) {
                allegro_message("Impossible de charger l'image: %s", !random_image2);
                return -1;
            }
            random_index3 = rand() % NUM_ICON;
            printf("the rand 3 = %d \n",random_index3);
            random_image3 = load_bitmap(icon[random_index3], NULL);
            if (!random_image3) {
                allegro_message("Impossible de charger l'image: %s", !random_image2);
                return -1;
            }

            //afficher les icons
            draw_sprite(game, random_image1, 187, 290);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            rest(1000); // Limiter le taux de rafraîchissement

            draw_sprite(game, random_image2, 275, 290);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            rest(1000); // Limiter le taux de rafraîchissement rest(10);

            draw_sprite(game, random_image3, 365, 290);
            blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
            rest(1000); // Limiter le taux de rafraîchissement

            //affichage du fond en fonction des icons (si il a gagné ou perdu)
            if (random_index3 == random_index1 && random_index1 == random_index2) {
                image = load_bitmap("fond_win.bmp", NULL);
                if (!image) {
                    allegro_message("Erreur lors du chargement de l'image.");
                    return -1;
                }
                // Dessiner l'image sur l'écran
                draw_sprite(game, image, -99, 0);
                blit(game, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //va copier un rectangle de pixel l'image sur la fenetre
                //afficher_image(fond, "fond.bmp");
                allegro_message("Tu as gagné, tu remportes un ticket ");
                rest(1000); // Limiter le taux de rafraîchissement
            } else {


                allegro_message("Tu as perdu, tu perds un ticket ");
                //afficher_image(fond, "fond.bmp");
                rest(3000); // Limiter le taux de rafraîchissement
            }


            // }
            // allegro_message("im here");

            //destroy_bitmap(image);


        } //while (game_start);

        //destroy_bitmap(random_image1);
        //destroy_bitmap(random_image2);
        //destroy_bitmap(random_image3);


        //affichage de la mmachine jackpot
        //afficher_image(fond,"fond.bmp");
        //allegro_message("Voulez-vous commencer une partie ? (appuyer 1 si oui et 0 si non ");
    allegro_exit();
}


END_OF_MAIN()