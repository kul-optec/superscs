clear;
rng('default');
rng(1);

n = 1000; m = ceil(n/5); s=ceil(n/10);

x_true=[randn(s,1);zeros(n-s,1)]; % true sparse signal
x_true = x_true(randperm(n));

density = 0.1;
rcA = .01;
A=sprandn(m,n,density,rcA);

b = A*x_true + 0.1*randn(m,1);
mu = 1;

do_super_scs = 1;

tic;
cvx_begin
    cvx_solver scs
    cvx_solver_settings('eps', 1e-7,...
        'scale', 1,...
        'do_super_scs',do_super_scs,...
        'direction', 150,...
        'k0', 0,...
        'memory', 20,...
        'rho_x', 0.001,...
        'verbose', 2, ...
        'do_record_progress',0, ...
        'use_indirect',1)
    cvx_solver_settings('dumpfile', 'lasso.mat');
    variable x_c(n)
    minimize(0.5*sum_square(A*x_c - b) + mu*norm(x_c,1))
cvx_end
toc
%load('lasso.mat')
%semilogy(info.progress_time, info.progress_respri,'linewidth',2)
%grid on