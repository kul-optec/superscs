/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Pantelis Sopasakis (https://alphaville.github.io),
 *                    Krina Menounou (https://www.linkedin.com/in/krinamenounou), 
 *                    Panagiotis Patrinos (http://homes.esat.kuleuven.be/~ppatrino)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */
/*! \page page_installation Installation
 * 
 * \tableofcontents
 * 
 * \section sec-install-guide Installation guide
 * 
 * <img src="images/installation.png" width="60%"/>
 * 
 * \subsection installation_in_c Linux and MacOSX
 * 
 * \htmlonly
 * <img src="images/linux_mac_build.png" height="80px"/>
 * \endhtmlonly
 * 
 * \subsubsection dependencies_superscs Dependencies
 * 
 * Before you proceed, make sure the following dependencies are installed: 
 * 
 * - <code>libblas-dev</code>
 * - <code>liblapack-dev</code>
 * 
 * if you intend to use SuperSCS via its python interface, you also need to 
 * install
 * 
 * - <code>python-numpy</code>
 * - <code>python-scipy</code>
 * 
 * In Linux run
 * 
 * ~~~~~
 * sudo apt-get install libblas-dev liblapack-dev
 * sudo apt-get install python-numpy python-scipy
 * ~~~~~
 * 
 * 
 * 
 * \subsubsection sec_linux_max_install Installation
 * 
 * First, you need to [download SuperSCS](https://github.com/kul-optec/superscs/archive/master.zip)
 * from the [github repo](https://github.com/kul-optec/superscs) of SuperSCS, or use the 
 * command:
 * 
 * ~~~~~
 * git clone 'https://github.com/kul-optec/superscs.git'
 * cd scs/
 * ~~~~~
 * 
 * Installation runs as simple as 
 * 
 * ~~~~~
 * make
 * ~~~~~
 * 
 * Once \c make finishes, the library files will be in <code>out/</code>.
 *  
 * If you want to run the tests, do 
 *
 * ~~~~~
 * make run-test
 * ~~~~~
 * 
 * If, additionally, you want to run the tests and perform a memory check
 * using [valgrind](http://valgrind.org), do 
 * 
 * ~~~~~
 * make run-test-mem
 * ~~~~~
 * 
 * For more advanced options, type in your terminal 
 * 
 * ~~~~~
 * make help
 * ~~~~~
 * 
 * 
 * 
 * \subsection docker_image_guide Docker image
 * 
 * \htmlonly
 * <img src="images/docker_guide.png" height="80px"/>
 * \endhtmlonly
 * 
 * Docker is the simplest and most reliable way to install SuperSCS. 
 * 
 * The engine of SuperSCS, the C library, can be installed using the image 
 * <code>kulforbes/superscs</code>.
 * 
 * Install it running:
 * 
 * ~~~~~
 * docker pull kulforbes/superscs
 * ~~~~~
 * 
 * If you haven't installed docker, do so by following 
 * <a href="https://docs.docker.com/install/#supported-platforms">this guide</a>.
 * 
 * You may then run the docker image and access it using an interactive
 * terminal by running
 * 
 * ~~~~~
 * docker run -it kulforbes/superscs
 * ~~~~~
 * 
 * All that is necessary to run SuperSCS in C has been installed. 
 * 
 * Compiling with SuperSCS is as simple as
 * 
 * ~~~~~
 * gcc superscs_test.c -o superscs_test -lscsindir -lblas -llapack -lm
 * ~~~~~
 * 
 * 
 * 
 * 
 * 
 * \section sec-interfaces Interfaces
 * 
 * \subsection sec_matlab MATLAB
 * 
 * \htmlonly
 * <img src="images/matlab_guide.png" height="80px"/>
 * \endhtmlonly
 * 
 * To install <code>SuperSCS</code> in MATLAB, you need to build a MEX interface.
 * 
 * Do:
 *
 * \code{.cpp}
 *  cd matlab;
 *  make_scs;
 * \endcode
 * 
 * This should work. If not, please [report an issue](https://github.com/kul-optec/superscs/issues).
 * 
 * 
 * 
 * \subsection sec_cvx_matlab CVX MATLAB
 * 
 * \htmlonly
 * <img src="images/cvx_guide.png" height="80px"/>
 * \endhtmlonly
 * 
 * Necessary steps:
 * 
 * - Download and unpack <code>CVX 3.0</code> from [here](http://cvxr.com/cvx/beta/)
 * - You need to do a tiny modification in [<code>cvx/shims/cvx_scs.m</code>](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714)
 *   and comment-out lines 165-175. 
 *   Find the modified file [here](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714).
 * - Navigate to the <code>cvx</code> directory
 * - Run <code>cvx_setup</code>
 * - To use <code>SuperSCS</code>, we call <code>cvx</code> with <code>cvx_solver scs</code>
 *   and setting the parameter <code>do_super_scs</code> to 1.
 * 
 * Here is an example of an LP problem
 * ~~~~~{.m}
 * A(1,1) = 0.3; A(4,1) = -0.5;
 * A(2,2) = 0.7; A(4,2) =  0.9; A(3,3) = 0.2;
 * A = sparse(A);
 * n = size(A,2);
 * b = [0.2; 0.1; -0.1; 0.1];
 * c = [1;-2;-3];
 * 
 * cvx_begin
 *     cvx_solver scs
 *     cvx_solver_settings('eps', 1e-8, 'do_super_scs', 1, 'rho_x', 1,...
 *          'direction', 100, 'memory', 50);
 *     variable x(n);
 *     dual variable y;
 *     minimize( x'*x + c' * x );
 *     subject to
 *          y : A * x <= b;
 * cvx_end
 *~~~~~
 * 
 * We have chosen the SuperSCS mode with \f$\rho_x=1\f$, the restarted Broyden 
 * direction and memory equal to \f$50\f$.
 * 
 * We have set the tolerance to \f$10^{-8}\f$.
 * 
 * In case you encounter any problems, please [report an issue](https://github.com/kul-optec/superscs/issues).
 * 
 * \note This a pre-alpha unstable version, so there might be issues. 
 * 
 * \note For example, <code>cvx_precision</code> is not supported (you have to use 
 * <code>cvx_solver_settings('eps',...)</code>).
 * 
 * 
 * 
 * 
 * \subsection sec_installation_python Python
 * 
 * \htmlonly
 * <img src="images/py_guide.png" height="80px"/>
 * \endhtmlonly
 * 
 * In order to install the SuperSCS module for Python, \c cd to \c python/ and
 * run \c setup.py with the argument \c install:
 * 
 * ~~~~~{.sh}
 * cd python/
 * (sudo) python setup.py install
 * ~~~~~
 * 
 * You will then be able to import \c superscs into your Python code. 
 * 
 * Further documentation for the Python module can be found \ref secpython "here".
 * 
 * 
 */