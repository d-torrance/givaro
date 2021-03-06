// Copyright(c)'1994-2009 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.

/*! @file examples/Rational/iratrecon.C
 * @ingroup examples
 * @ingroup rationals
 * @example examples/Rational/iratrecon.C
 * @brief NO DOC
 */
#include <iostream>
#include <stdlib.h>
#include <givaro/givrational.h>
#include <givaro/givtimer.h>
#include <givaro/givinit.h>         // Givaro initialization

using namespace Givaro;

int main(int argc, char** argv)
{
    Integer f,m,k;
    if (argc > 1) f = Integer(argv[1]); else std::cin >> f;
    if (argc > 2) m = Integer(argv[2]); else std::cin >> m;

    QField<Rational> RD;
    Rational rec;

    Timer tim; tim.clear(); tim.start();
    if (argc > 3)
        RD.ratrecon(rec,f,m, Integer(argv[3]) );
    else
        RD.ratrecon(rec,f,m);
    tim.stop();
    std::cout << rec.nume() << "/" << rec.deno() << " = " << f << " mod " << m << std::endl;
    std::cerr << tim << std::endl;

    return 0;
}

