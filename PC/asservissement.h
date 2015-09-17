#ifndef ASSERVISSEMENT_H
#define ASSERVISSEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

int get_theta_actuel();
float float_get_x_actuel();
float float_get_y_actuel();
void set_trajectoire_xy_absolu(int x, int y);

#ifdef __cplusplus
}
#endif

#endif
