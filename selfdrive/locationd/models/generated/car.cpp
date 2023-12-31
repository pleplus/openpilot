#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3994003449420885177) {
   out_3994003449420885177[0] = delta_x[0] + nom_x[0];
   out_3994003449420885177[1] = delta_x[1] + nom_x[1];
   out_3994003449420885177[2] = delta_x[2] + nom_x[2];
   out_3994003449420885177[3] = delta_x[3] + nom_x[3];
   out_3994003449420885177[4] = delta_x[4] + nom_x[4];
   out_3994003449420885177[5] = delta_x[5] + nom_x[5];
   out_3994003449420885177[6] = delta_x[6] + nom_x[6];
   out_3994003449420885177[7] = delta_x[7] + nom_x[7];
   out_3994003449420885177[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2836171143531724637) {
   out_2836171143531724637[0] = -nom_x[0] + true_x[0];
   out_2836171143531724637[1] = -nom_x[1] + true_x[1];
   out_2836171143531724637[2] = -nom_x[2] + true_x[2];
   out_2836171143531724637[3] = -nom_x[3] + true_x[3];
   out_2836171143531724637[4] = -nom_x[4] + true_x[4];
   out_2836171143531724637[5] = -nom_x[5] + true_x[5];
   out_2836171143531724637[6] = -nom_x[6] + true_x[6];
   out_2836171143531724637[7] = -nom_x[7] + true_x[7];
   out_2836171143531724637[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4300544645246884683) {
   out_4300544645246884683[0] = 1.0;
   out_4300544645246884683[1] = 0;
   out_4300544645246884683[2] = 0;
   out_4300544645246884683[3] = 0;
   out_4300544645246884683[4] = 0;
   out_4300544645246884683[5] = 0;
   out_4300544645246884683[6] = 0;
   out_4300544645246884683[7] = 0;
   out_4300544645246884683[8] = 0;
   out_4300544645246884683[9] = 0;
   out_4300544645246884683[10] = 1.0;
   out_4300544645246884683[11] = 0;
   out_4300544645246884683[12] = 0;
   out_4300544645246884683[13] = 0;
   out_4300544645246884683[14] = 0;
   out_4300544645246884683[15] = 0;
   out_4300544645246884683[16] = 0;
   out_4300544645246884683[17] = 0;
   out_4300544645246884683[18] = 0;
   out_4300544645246884683[19] = 0;
   out_4300544645246884683[20] = 1.0;
   out_4300544645246884683[21] = 0;
   out_4300544645246884683[22] = 0;
   out_4300544645246884683[23] = 0;
   out_4300544645246884683[24] = 0;
   out_4300544645246884683[25] = 0;
   out_4300544645246884683[26] = 0;
   out_4300544645246884683[27] = 0;
   out_4300544645246884683[28] = 0;
   out_4300544645246884683[29] = 0;
   out_4300544645246884683[30] = 1.0;
   out_4300544645246884683[31] = 0;
   out_4300544645246884683[32] = 0;
   out_4300544645246884683[33] = 0;
   out_4300544645246884683[34] = 0;
   out_4300544645246884683[35] = 0;
   out_4300544645246884683[36] = 0;
   out_4300544645246884683[37] = 0;
   out_4300544645246884683[38] = 0;
   out_4300544645246884683[39] = 0;
   out_4300544645246884683[40] = 1.0;
   out_4300544645246884683[41] = 0;
   out_4300544645246884683[42] = 0;
   out_4300544645246884683[43] = 0;
   out_4300544645246884683[44] = 0;
   out_4300544645246884683[45] = 0;
   out_4300544645246884683[46] = 0;
   out_4300544645246884683[47] = 0;
   out_4300544645246884683[48] = 0;
   out_4300544645246884683[49] = 0;
   out_4300544645246884683[50] = 1.0;
   out_4300544645246884683[51] = 0;
   out_4300544645246884683[52] = 0;
   out_4300544645246884683[53] = 0;
   out_4300544645246884683[54] = 0;
   out_4300544645246884683[55] = 0;
   out_4300544645246884683[56] = 0;
   out_4300544645246884683[57] = 0;
   out_4300544645246884683[58] = 0;
   out_4300544645246884683[59] = 0;
   out_4300544645246884683[60] = 1.0;
   out_4300544645246884683[61] = 0;
   out_4300544645246884683[62] = 0;
   out_4300544645246884683[63] = 0;
   out_4300544645246884683[64] = 0;
   out_4300544645246884683[65] = 0;
   out_4300544645246884683[66] = 0;
   out_4300544645246884683[67] = 0;
   out_4300544645246884683[68] = 0;
   out_4300544645246884683[69] = 0;
   out_4300544645246884683[70] = 1.0;
   out_4300544645246884683[71] = 0;
   out_4300544645246884683[72] = 0;
   out_4300544645246884683[73] = 0;
   out_4300544645246884683[74] = 0;
   out_4300544645246884683[75] = 0;
   out_4300544645246884683[76] = 0;
   out_4300544645246884683[77] = 0;
   out_4300544645246884683[78] = 0;
   out_4300544645246884683[79] = 0;
   out_4300544645246884683[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4085036891446952713) {
   out_4085036891446952713[0] = state[0];
   out_4085036891446952713[1] = state[1];
   out_4085036891446952713[2] = state[2];
   out_4085036891446952713[3] = state[3];
   out_4085036891446952713[4] = state[4];
   out_4085036891446952713[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4085036891446952713[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4085036891446952713[7] = state[7];
   out_4085036891446952713[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7682267835197150451) {
   out_7682267835197150451[0] = 1;
   out_7682267835197150451[1] = 0;
   out_7682267835197150451[2] = 0;
   out_7682267835197150451[3] = 0;
   out_7682267835197150451[4] = 0;
   out_7682267835197150451[5] = 0;
   out_7682267835197150451[6] = 0;
   out_7682267835197150451[7] = 0;
   out_7682267835197150451[8] = 0;
   out_7682267835197150451[9] = 0;
   out_7682267835197150451[10] = 1;
   out_7682267835197150451[11] = 0;
   out_7682267835197150451[12] = 0;
   out_7682267835197150451[13] = 0;
   out_7682267835197150451[14] = 0;
   out_7682267835197150451[15] = 0;
   out_7682267835197150451[16] = 0;
   out_7682267835197150451[17] = 0;
   out_7682267835197150451[18] = 0;
   out_7682267835197150451[19] = 0;
   out_7682267835197150451[20] = 1;
   out_7682267835197150451[21] = 0;
   out_7682267835197150451[22] = 0;
   out_7682267835197150451[23] = 0;
   out_7682267835197150451[24] = 0;
   out_7682267835197150451[25] = 0;
   out_7682267835197150451[26] = 0;
   out_7682267835197150451[27] = 0;
   out_7682267835197150451[28] = 0;
   out_7682267835197150451[29] = 0;
   out_7682267835197150451[30] = 1;
   out_7682267835197150451[31] = 0;
   out_7682267835197150451[32] = 0;
   out_7682267835197150451[33] = 0;
   out_7682267835197150451[34] = 0;
   out_7682267835197150451[35] = 0;
   out_7682267835197150451[36] = 0;
   out_7682267835197150451[37] = 0;
   out_7682267835197150451[38] = 0;
   out_7682267835197150451[39] = 0;
   out_7682267835197150451[40] = 1;
   out_7682267835197150451[41] = 0;
   out_7682267835197150451[42] = 0;
   out_7682267835197150451[43] = 0;
   out_7682267835197150451[44] = 0;
   out_7682267835197150451[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7682267835197150451[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7682267835197150451[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7682267835197150451[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7682267835197150451[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7682267835197150451[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7682267835197150451[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7682267835197150451[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7682267835197150451[53] = -9.8000000000000007*dt;
   out_7682267835197150451[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7682267835197150451[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7682267835197150451[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7682267835197150451[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7682267835197150451[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7682267835197150451[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7682267835197150451[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7682267835197150451[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7682267835197150451[62] = 0;
   out_7682267835197150451[63] = 0;
   out_7682267835197150451[64] = 0;
   out_7682267835197150451[65] = 0;
   out_7682267835197150451[66] = 0;
   out_7682267835197150451[67] = 0;
   out_7682267835197150451[68] = 0;
   out_7682267835197150451[69] = 0;
   out_7682267835197150451[70] = 1;
   out_7682267835197150451[71] = 0;
   out_7682267835197150451[72] = 0;
   out_7682267835197150451[73] = 0;
   out_7682267835197150451[74] = 0;
   out_7682267835197150451[75] = 0;
   out_7682267835197150451[76] = 0;
   out_7682267835197150451[77] = 0;
   out_7682267835197150451[78] = 0;
   out_7682267835197150451[79] = 0;
   out_7682267835197150451[80] = 1;
}
void h_25(double *state, double *unused, double *out_567823590266453003) {
   out_567823590266453003[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3999943544051968747) {
   out_3999943544051968747[0] = 0;
   out_3999943544051968747[1] = 0;
   out_3999943544051968747[2] = 0;
   out_3999943544051968747[3] = 0;
   out_3999943544051968747[4] = 0;
   out_3999943544051968747[5] = 0;
   out_3999943544051968747[6] = 1;
   out_3999943544051968747[7] = 0;
   out_3999943544051968747[8] = 0;
}
void h_24(double *state, double *unused, double *out_8280871722589836637) {
   out_8280871722589836637[0] = state[4];
   out_8280871722589836637[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1744095468928151118) {
   out_1744095468928151118[0] = 0;
   out_1744095468928151118[1] = 0;
   out_1744095468928151118[2] = 0;
   out_1744095468928151118[3] = 0;
   out_1744095468928151118[4] = 1;
   out_1744095468928151118[5] = 0;
   out_1744095468928151118[6] = 0;
   out_1744095468928151118[7] = 0;
   out_1744095468928151118[8] = 0;
   out_1744095468928151118[9] = 0;
   out_1744095468928151118[10] = 0;
   out_1744095468928151118[11] = 0;
   out_1744095468928151118[12] = 0;
   out_1744095468928151118[13] = 0;
   out_1744095468928151118[14] = 1;
   out_1744095468928151118[15] = 0;
   out_1744095468928151118[16] = 0;
   out_1744095468928151118[17] = 0;
}
void h_30(double *state, double *unused, double *out_5044895097204645462) {
   out_5044895097204645462[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8527639874179576945) {
   out_8527639874179576945[0] = 0;
   out_8527639874179576945[1] = 0;
   out_8527639874179576945[2] = 0;
   out_8527639874179576945[3] = 0;
   out_8527639874179576945[4] = 1;
   out_8527639874179576945[5] = 0;
   out_8527639874179576945[6] = 0;
   out_8527639874179576945[7] = 0;
   out_8527639874179576945[8] = 0;
}
void h_26(double *state, double *unused, double *out_5648210981881122979) {
   out_5648210981881122979[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7741446862926024971) {
   out_7741446862926024971[0] = 0;
   out_7741446862926024971[1] = 0;
   out_7741446862926024971[2] = 0;
   out_7741446862926024971[3] = 0;
   out_7741446862926024971[4] = 0;
   out_7741446862926024971[5] = 0;
   out_7741446862926024971[6] = 0;
   out_7741446862926024971[7] = 1;
   out_7741446862926024971[8] = 0;
}
void h_27(double *state, double *unused, double *out_4433849677394392642) {
   out_4433849677394392642[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7744340887729549760) {
   out_7744340887729549760[0] = 0;
   out_7744340887729549760[1] = 0;
   out_7744340887729549760[2] = 0;
   out_7744340887729549760[3] = 1;
   out_7744340887729549760[4] = 0;
   out_7744340887729549760[5] = 0;
   out_7744340887729549760[6] = 0;
   out_7744340887729549760[7] = 0;
   out_7744340887729549760[8] = 0;
}
void h_29(double *state, double *unused, double *out_7425066469838863811) {
   out_7425066469838863811[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8017408529865184761) {
   out_8017408529865184761[0] = 0;
   out_8017408529865184761[1] = 1;
   out_8017408529865184761[2] = 0;
   out_8017408529865184761[3] = 0;
   out_8017408529865184761[4] = 0;
   out_8017408529865184761[5] = 0;
   out_8017408529865184761[6] = 0;
   out_8017408529865184761[7] = 0;
   out_8017408529865184761[8] = 0;
}
void h_28(double *state, double *unused, double *out_1821975044564654612) {
   out_1821975044564654612[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5346936526774836281) {
   out_5346936526774836281[0] = 1;
   out_5346936526774836281[1] = 0;
   out_5346936526774836281[2] = 0;
   out_5346936526774836281[3] = 0;
   out_5346936526774836281[4] = 0;
   out_5346936526774836281[5] = 0;
   out_5346936526774836281[6] = 0;
   out_5346936526774836281[7] = 0;
   out_5346936526774836281[8] = 0;
}
void h_31(double *state, double *unused, double *out_7195441666554219438) {
   out_7195441666554219438[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8367654965159376447) {
   out_8367654965159376447[0] = 0;
   out_8367654965159376447[1] = 0;
   out_8367654965159376447[2] = 0;
   out_8367654965159376447[3] = 0;
   out_8367654965159376447[4] = 0;
   out_8367654965159376447[5] = 0;
   out_8367654965159376447[6] = 0;
   out_8367654965159376447[7] = 0;
   out_8367654965159376447[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3994003449420885177) {
  err_fun(nom_x, delta_x, out_3994003449420885177);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2836171143531724637) {
  inv_err_fun(nom_x, true_x, out_2836171143531724637);
}
void car_H_mod_fun(double *state, double *out_4300544645246884683) {
  H_mod_fun(state, out_4300544645246884683);
}
void car_f_fun(double *state, double dt, double *out_4085036891446952713) {
  f_fun(state,  dt, out_4085036891446952713);
}
void car_F_fun(double *state, double dt, double *out_7682267835197150451) {
  F_fun(state,  dt, out_7682267835197150451);
}
void car_h_25(double *state, double *unused, double *out_567823590266453003) {
  h_25(state, unused, out_567823590266453003);
}
void car_H_25(double *state, double *unused, double *out_3999943544051968747) {
  H_25(state, unused, out_3999943544051968747);
}
void car_h_24(double *state, double *unused, double *out_8280871722589836637) {
  h_24(state, unused, out_8280871722589836637);
}
void car_H_24(double *state, double *unused, double *out_1744095468928151118) {
  H_24(state, unused, out_1744095468928151118);
}
void car_h_30(double *state, double *unused, double *out_5044895097204645462) {
  h_30(state, unused, out_5044895097204645462);
}
void car_H_30(double *state, double *unused, double *out_8527639874179576945) {
  H_30(state, unused, out_8527639874179576945);
}
void car_h_26(double *state, double *unused, double *out_5648210981881122979) {
  h_26(state, unused, out_5648210981881122979);
}
void car_H_26(double *state, double *unused, double *out_7741446862926024971) {
  H_26(state, unused, out_7741446862926024971);
}
void car_h_27(double *state, double *unused, double *out_4433849677394392642) {
  h_27(state, unused, out_4433849677394392642);
}
void car_H_27(double *state, double *unused, double *out_7744340887729549760) {
  H_27(state, unused, out_7744340887729549760);
}
void car_h_29(double *state, double *unused, double *out_7425066469838863811) {
  h_29(state, unused, out_7425066469838863811);
}
void car_H_29(double *state, double *unused, double *out_8017408529865184761) {
  H_29(state, unused, out_8017408529865184761);
}
void car_h_28(double *state, double *unused, double *out_1821975044564654612) {
  h_28(state, unused, out_1821975044564654612);
}
void car_H_28(double *state, double *unused, double *out_5346936526774836281) {
  H_28(state, unused, out_5346936526774836281);
}
void car_h_31(double *state, double *unused, double *out_7195441666554219438) {
  h_31(state, unused, out_7195441666554219438);
}
void car_H_31(double *state, double *unused, double *out_8367654965159376447) {
  H_31(state, unused, out_8367654965159376447);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
