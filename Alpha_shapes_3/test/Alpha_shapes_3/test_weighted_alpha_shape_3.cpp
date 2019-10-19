// Copyright (c) 1999-2003  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Alpha_shape_3.h>
#include <CGAL/Alpha_shape_cell_base_3.h>
#include <CGAL/Alpha_shape_vertex_base_3.h>
#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Triangulation_data_structure_3.h>

#include <CGAL/_test_weighted_alpha_shape_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Regular_triangulation_vertex_base_3<K>        Rvb;
typedef CGAL::Alpha_shape_vertex_base_3<K,Rvb>              Vb;

typedef CGAL::Regular_triangulation_cell_base_3<K>          Rcb;
typedef CGAL::Alpha_shape_cell_base_3<K,Rcb>                Cb;
typedef CGAL::Triangulation_data_structure_3<Vb,Cb>         Tds;

typedef CGAL::Regular_triangulation_3<K,Tds>                Triangulation_3;
typedef CGAL::Alpha_shape_3<Triangulation_3>                Alpha_shape_3;

//using exact filtered traits
typedef CGAL::Alpha_shape_vertex_base_3<K,Rvb,CGAL::Tag_true,CGAL::Tag_true>   EF_Vb;
typedef CGAL::Alpha_shape_cell_base_3<K,Rcb,CGAL::Tag_true,CGAL::Tag_true>     EF_Cb;
typedef CGAL::Triangulation_data_structure_3<EF_Vb,EF_Cb>   EF_Tds;

typedef CGAL::Regular_triangulation_3<K,EF_Tds>        EF_Triangulation_3;
typedef CGAL::Alpha_shape_3<EF_Triangulation_3,CGAL::Tag_true>            EF_Alpha_shape_3;

int main()
{
  _test_weighted_alpha_shape_3<Alpha_shape_3>();
  _test_weighted_alpha_shape_3<EF_Alpha_shape_3>();
  return 0;
}

// MipsPro prefers this after the other instantiations...
// Explicit instantiation of the whole class :
template class CGAL::Alpha_shape_3<Triangulation_3>;
template class CGAL::Alpha_shape_3<EF_Triangulation_3,CGAL::Tag_true>;
