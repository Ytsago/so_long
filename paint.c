#include "mlx.h"
#include "mlx_int.h"

void *mlx;
t_win_list *win1;
unsigned char r = 255;
unsigned char g = 0;
unsigned char b = 0;
int			b_pressed = 0;

// Fonction qui gère les événements de touche
int key_win1(int key, void *param)
{
	printf("%d", key);
    if (key == 0xFF1B) // Touche Échap pour quitter
         mlx_destroy_window(mlx, win1);
    return (0);
}

// Fonction qui met à jour les couleurs pour créer l'effet arc-en-ciel
void updateRainbowColors(unsigned char *r, unsigned char *g, unsigned char *b)
{
    if (*r == 255 && *g < 255 && *b == 0)         // Rouge -> Jaune
        (*g)++;
    else if (*g == 255 && *r > 0 && *b == 0)      // Jaune -> Vert
        (*r)--;
    else if (*g == 255 && *b < 255 && *r == 0)    // Vert -> Cyan
        (*b)++;
    else if (*b == 255 && *g > 0 && *r == 0)      // Cyan -> Bleu
        (*g)--;
    else if (*b == 255 && *r < 255 && *g == 0)    // Bleu -> Magenta
        (*r)++;
    else if (*r == 255 && *b > 0 && *g == 0)      // Magenta -> Rouge
        (*b)--;
}

// Fonction pour dessiner un carré de couleur à une position donnée
void paint_square(void *_mlx, void *_window, int x, int y, int width, int height, int color)
{
    for (int i = -width / 2; i < width / 2; i++)
    {
        for (int yy = -height / 2; yy < height / 2; yy++)
        {
            mlx_pixel_put(_mlx, _window, x + i, y + yy, color);
        }
    }
}

int button_pressed(void)
{
	if (!b_pressed)
		b_pressed = 1;
	else
		b_pressed = 0;
}

// Fonction qui gère les événements de souris
int mouse_win(void *p)
{
	if (!b_pressed)
		return 0;

	int x;
	int y;
	x = 0;
	y = 0;
	mlx_mouse_get_pos(mlx, win1, &x, &y);
    // Mettre à jour les couleurs de l'arc-en-ciel
    updateRainbowColors(&r, &g, &b);

    // Créer la couleur au format RGB
    int color = ((r << 16) | (g << 8) | b);

    // Dessiner un carré à la position de la souris
    paint_square(mlx, win1, x, y, rand() % 100, rand() % 100, color);

    return (0);
}

int main()
{
    // Initialisation de mlx et création de la fenêtre
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Erreur d'initialisation de mlx.\n");
        return (1);
    }
    win1 = mlx_new_window(mlx, 1000, 1000, "Arc-en-ciel");
    if (!win1)
    {
        printf("Erreur de création de la fenêtre.\n");
        return (1);
    }

    // Enregistrement des hooks pour la gestion des événements
	mlx_hook(win1, 4, ButtonPressMask, button_pressed, NULL);
	mlx_hook(win1, ButtonRelease, ButtonReleaseMask, button_pressed, NULL);
	mlx_hook(win1, 6, PointerMotionMask, mouse_win, NULL);
	// mlx_key_hook(win1, key_win1, 0);
	mlx_key_hook(mlx, key_win1, NULL);
    // Lancer la boucle principale de mlx pour écouter les événements
    mlx_loop(mlx);

    // Nettoyage et destruction de la fenêtre
    mlx_destroy_window(mlx, win1);
    free(mlx);
    return 0;
}