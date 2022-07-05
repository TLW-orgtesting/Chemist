
/*
 * This file is autogenerated by generate_densities.py.  Any modifications made
 * in this file will be lost next time generate_densities.py is run.
 */

#include "chemist/defaults/nwx_atomic_densities.hpp"
#include <stdexcept>
#include <string>

namespace chemist::detail_ {

std::vector<std::vector<double>> get_atomic_density_(const std::string& name,
                                                     std::size_t Z) {
    if(name == "6-31g") {
        return six_dash_31g_density(Z);
    } else if(name == "sto-3g") {
        return sto_dash_3g_density(Z);
    } else if(name == "sto-6g") {
        return sto_dash_6g_density(Z);
    } else
        throw std::out_of_range("Basis not available for SAD guess");
} // end get_atomic_density_

} // namespace chemist::detail_
