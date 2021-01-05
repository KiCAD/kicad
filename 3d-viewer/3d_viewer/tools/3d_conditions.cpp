/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2020 Ian McInerney <ian.s.mcinerney at ieee.org>
 * Copyright (C) 1992-2020 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <3d_canvas/board_adapter.h>
#include <3d_viewer/tools/3d_conditions.h>

#include <functional>

using namespace std::placeholders;


SELECTION_CONDITION EDA_3D_CONDITIONS::MaterialMode( MATERIAL_MODE aMaterial )
{
    return std::bind( &EDA_3D_CONDITIONS::materialModeFunction, _1, m_adapter, aMaterial );
}


SELECTION_CONDITION EDA_3D_CONDITIONS::Flag( DISPLAY3D_FLG aFlag )
{
    return std::bind( &EDA_3D_CONDITIONS::flagFunction, _1, m_adapter, aFlag );
}


SELECTION_CONDITION EDA_3D_CONDITIONS::GridSize( GRID3D_TYPE aGridSize )
{
    return std::bind( &EDA_3D_CONDITIONS::gridSizeFunction, _1, m_adapter, aGridSize );
}


bool EDA_3D_CONDITIONS::materialModeFunction( const SELECTION& aSelection,
                                              BOARD_ADAPTER* aAdapter,
                                              MATERIAL_MODE aMaterial )
{
    return aAdapter->GetMaterialMode() == aMaterial;
}


bool EDA_3D_CONDITIONS::flagFunction( const SELECTION& aSelection,
                                      BOARD_ADAPTER* aAdapter,
                                      DISPLAY3D_FLG aFlag )
{
    return aAdapter->GetFlag( aFlag );
}


bool EDA_3D_CONDITIONS::gridSizeFunction( const SELECTION& aSelection,
                                          BOARD_ADAPTER* aAdapter,
                                          GRID3D_TYPE aGridSize )
{
    return aAdapter->GetGridType() == aGridSize;
}
