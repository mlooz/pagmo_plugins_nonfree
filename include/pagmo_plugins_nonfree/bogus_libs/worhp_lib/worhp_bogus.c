#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "worhp_bogus.h"

inline double closed_interval_rand(double x0, double x1)
{
    return x0 + (x1 - x0) * rand() / ((double)RAND_MAX);
}

DLL_PUBLIC void ReadParams(int *a, const char b[], Params *c){}
DLL_PUBLIC void WorhpPreInit(OptVar *o, Workspace *w, Params *p, Control *c){}
DLL_PUBLIC void WorhpInit(OptVar *o, Workspace *w, Params *p, Control *c)
{
    o->X = calloc(o->n, sizeof(double));
    o->G = calloc(o->m, sizeof(double));
    o->Lambda = calloc(o->m, sizeof(double));
    o->XL = calloc(o->n, sizeof(double));
    o->XU = calloc(o->n, sizeof(double));
    o->Mu = calloc(o->m, sizeof(double));
    o->GL = calloc(o->m, sizeof(double));
    o->GU = calloc(o->m, sizeof(double));
    w->DF.row = calloc(w->DF.nnz, sizeof(int));
    w->DF.val = calloc(w->DF.nnz, sizeof(double));
    w->DG.row = calloc(w->DG.nnz, sizeof(int));
    w->DG.col = calloc(w->DG.nnz, sizeof(int));
    w->DG.val = calloc(w->DG.nnz, sizeof(double));
    w->HM.row = calloc(w->HM.nnz, sizeof(int));
    w->HM.col = calloc(w->HM.nnz, sizeof(int));
    w->HM.val = calloc(w->HM.nnz, sizeof(double));
    w->ScaleObj = 1;
    c->status = 0; // to ensure it will enter the main loop in worhp.hpp
    srand((unsigned int)(time(NULL)));
}
DLL_PUBLIC bool GetUserAction(const Control *c, int b)
{
    return true;
}
DLL_PUBLIC void DoneUserAction(Control *a, int b){}
DLL_PUBLIC void IterationOutput(OptVar *o, Workspace *w, Params *p, Control *c){}
DLL_PUBLIC void Worhp(OptVar *o, Workspace *w, Params *p, Control *c)
{
    if (o->F < 1) {
     c->status = 10000;
    }
    // Random vector
    int j;
    for (j = 0; j < o->n; ++j) {
        o->X[j] = closed_interval_rand(o->XL[j], o->XU[j]);
    }
}

DLL_PUBLIC void StatusMsg(OptVar *o, Workspace *w, Params *p, Control *c){
    printf("All went great!!!! What a glamorous Success!!\n");
}

DLL_PUBLIC void StatusMsgString(OptVar *o, Workspace *w, Params *p, Control *c, char message[]){
    strcpy(message, "All went great!!!! What a glamorous Success!!\n");
}

DLL_PUBLIC void WorhpFree(OptVar *o, Workspace *w, Params *p, Control *c)
{
    free(o->X);
    free(o->G);
    free(o->Lambda);
    free(o->XL);
    free(o->XU);
    free(o->Mu);
    free(o->GL);
    free(o->GU);
    free(w->DF.row);
    free(w->DF.val);
    free(w->DG.row);
    free(w->DG.col);
    free(w->DG.val);
    free(w->HM.row);
    free(w->HM.col);
    free(w->HM.val);
}
DLL_PUBLIC void WorhpFidif(OptVar *o, Workspace *w, Params *p, Control *c){}
DLL_PUBLIC bool WorhpSetBoolParam(Params *p, const char *stropt, bool b)
{
    char *invalid;
    invalid = "invalid_bool_option";
    if (strcmp(stropt, invalid) == 0) {
        return 0;
    } else {
        return 1;
    }
}
DLL_PUBLIC bool WorhpSetIntParam(Params *p, const char *stropt, int b)
{
    char *invalid;
    invalid = "invalid_int_option";
    if (strcmp(stropt, invalid) == 0) {
        return 0;
    } else {
        return 1;
    }
}
DLL_PUBLIC bool WorhpSetDoubleParam(Params *p, const char *stropt, double b)
{
    char *invalid;
    invalid = "invalid_double_option";
    if (strcmp(stropt, invalid) == 0) {
        return 0;
    } else {
        return 1;
    }
}
DLL_PUBLIC void SetWorhpPrint(worhp_print_t l1){}

DLL_PUBLIC void WorhpVersion(int *major, int *minor, char patch[PATCH_STRING_LENGTH])
{
    strcpy(patch, "1");
    *major = 1;
    *minor = 12;
};
