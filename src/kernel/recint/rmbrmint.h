/* rmint/rmint.h - Class definition of rmint<K,MG_INACTIVE> from RecInt library

Copyright Université Joseph Fourier - Grenoble
Contributors :
    Alexis BREUST (alexis.breust@gmail.com 2014)
	Christophe CHABOT (christophechabotcc@gmail.com 2011)
    Jean-Guillaume Dumas

Time-stamp: <20 Jun 12 10:31:24 Jean-Guillaume.Dumas@imag.fr>

This software is a computer program whose purpose is to provide an fixed precision arithmetic library.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
*/

#ifndef RMINT_BASIC_RMINT_H
#define RMINT_BASIC_RMINT_H

/* If not previously defined, MG_DEFAULT is set
   for this file to run well. */
#if not defined(MG_DEFAULT)
#define MG_DEFAULT MG_INACTIVE
#endif

#include "rutools.h" /* mod_n() */
#include "rmdefine.h"

// --------------------------------------------------------------
// -------- Declaration of class rmint (no Montgomery) ----------

namespace RecInt
{
    /* For modular calculus in non-Montgomery mode */
    template <size_t K> class rmint<K, MGI> {
    public:
        // p is the module (must be > 1)
        static ruint<K> p;
        // Current value (always < p)
        ruint<K> Value;
        
        // Constructors
        rmint() : Value(0) {}
        rmint(const ruint<K>& c) : Value(c) {}
        rmint(const rmint<K, MGI>& c) : Value(c.Value) {}
        rmint(const rmint<K, MGA>& c) : Value(c.Value) { reduction(*this); }
        template <typename T, IS_UNSIGNED(T, int) = 0> rmint(const T b) : Value(b) { mod_n(Value, p); }
        template <typename T, IS_SIGNED(T, int) = 0>   rmint(const T b) : Value((b < 0)? -b : b)
            { mod_n(Value, p); if (b < 0) sub(Value, p, Value); }
        rmint(const double& b) : Value((b < 0)? -b : b)
            { mod_n(Value, p); if (b < 0) sub(Value, p, Value); }

        // Cast
        template <typename T, IS_ARITH(T, int) = 0> operator T() const { return T(Value); }
        
        // Module functions
        static void init_module(const ruint<K>& p);
        static void get_module(ruint<K>& p);
    };

    /* Declaration of module */
    template <size_t K> ruint<K> rmint<K, MGI>::p = 0;
    
    typedef rmint<6> rmint64;
    typedef rmint<7> rmint128;
    typedef rmint<8> rmint256;
    typedef rmint<9> rmint512;
}

#endif
