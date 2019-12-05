/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 1992-2019 KiCad Developers, see AUTHORS.txt for contributors.
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

/**
 * @file sch_iref.h
 * @brief Definitions of the SCH_IREF class and derivatives for Eeschema.
 */

#ifndef CLASS_IREF_H
#define CLASS_IREF_H


#include <macros.h>

class SCH_TEXT;
class SCH_GLOBALLABEL;

class SCH_IREF : public SCH_TEXT
{
public:
    SCH_IREF( const wxPoint& pos = wxPoint( 0, 0 ), const wxString& text = wxEmptyString,
            SCH_GLOBALLABEL* aParent = nullptr, KICAD_T aType = SCH_IREF_T );

    ~SCH_IREF() { }

    static inline bool ClassOf( const EDA_ITEM* aItem )
    {
        return aItem && SCH_IREF_T == aItem->Type();
    }

    wxString GetClass() const override
    {
        return wxT( "SCH_IREF" );
    }

    EDA_ITEM* Clone() const override;

    std::vector<int>* GetRefTable() { return &m_refTable; }

    bool IsDangling() const override { return false; }
    wxPoint GetSchematicTextOffset() const override { return wxPoint(0, 0); }

    void SetLabelSpinStyle( int aSpinStyle ) override;

    void CopyParentStyle();
    void PlaceAtDefaultPosition();

    SCH_GLOBALLABEL* GetParent() { return m_parent; }
    void SetParent( SCH_GLOBALLABEL* parent ) { m_parent = parent; }

    int GetOwnPageNumber() { return m_ownPageNumber; }
    void SetOwnPageNumber( int page ) { m_ownPageNumber = page; }

    SCH_SCREEN* GetScreen() { return m_screen; }
    void SetScreen( SCH_SCREEN* screen ) { m_screen = screen; }

private:
    std::vector<int> m_refTable;
    SCH_GLOBALLABEL* m_parent;
    int              m_ownPageNumber;
    SCH_SCREEN*      m_screen;
};

#endif
