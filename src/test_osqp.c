#include <osqp/osqp.h>
#include <stdio.h>

int main(void) {
    
    OSQPInt n = 2;  // Variable
    OSQPInt m = 3;  // Constraints

    OSQPFloat P_x[] = {1.0,1.0};
    OSQPInt P_i[] = {0,1};
    OSQPInt P_p[] = {0, 1,2};
    OSQPInt P_nnz = 2;

    OSQPFloat q[] = {0.0,0.0};
    
    OSQPFloat A_x[] = {1.0,1.0,1.0,1.0};
    OSQPInt A_i[] = {0,1,0,2};
    OSQPInt A_p[] = {0,2,4};
    OSQPInt A_nnz = 4;

    OSQPFloat l[] = {1.0,0.0,0.0};
    OSQPFloat u[] = {1.0,OSQP_INFTY,OSQP_INFTY};


    OSQPCscMatrix *P = OSQPCscMatrix_new(n,n,P_nnz, P_x, P_i, P_p);
    OSQPCscMatrix *A = OSQPCscMatrix_new(m,n,A_nnz, A_x,A_i,A_p);

    OSQPSettings *settings = OSQPSettings_new();
    settings->verbose = 0;
    settings-> polishing = 1;
    settings-> polish_refine_iter =10;
    settings-> eps_abs =1e-9;
    settings-> eps_rel = 1e-9;
    settings-> max_iter = 20000;

    OSQPSolver *solver = NULL;
    OSQPInt exitflag = osqp_setup(&solver,P,q,A,l,u,m,n,settings);
    if (exitflag){
        fprintf(stderr,"setup failed: %d\n", (int)exitflag);
        return (int)exitflag;
    };

    exitflag = osqp_solve(solver);
    if (!exitflag && solver->info->status_val == OSQP_SOLVED){
        printf("Status: %s\n", solver->info->status);
        printf("x = [%.6f, %.6f]\n", solver->solution->x[0],solver->solution->x[1]);
        printf("Objective = %.6f\n",solver->info->obj_val);
    }else {
        printf("Solver status: %s (code %d)\n",solver->info->status, (int)exitflag);
    };


    //Cleanup
    osqp_cleanup(solver);
    OSQPCscMatrix_free(A);
    OSQPCscMatrix_free(P);
    OSQPSettings_free(settings);

    return (int)exitflag;

}