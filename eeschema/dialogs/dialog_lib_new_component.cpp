/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2009 Wayne Stambaugh <stambaughw@verizon.net>
 * Copyright (C) 2016-2019 KiCad Developers, see AUTHORS.txt for contributors.
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

#include <dialog_lib_new_component.h>
#include <sch_validators.h>
#include <template_fieldnames.h>

DIALOG_LIB_NEW_COMPONENT::DIALOG_LIB_NEW_COMPONENT( wxWindow* parent,
                                                    const wxArrayString* aRootSymbolNames ) :
    DIALOG_LIB_NEW_COMPONENT_BASE( parent )
{
    if( aRootSymbolNames && aRootSymbolNames->GetCount() )
        m_comboInheritanceSelect->Append( *aRootSymbolNames );

    m_textName->SetValidator( SCH_FIELD_VALIDATOR( true, VALUE ) );
    m_textReference->SetValidator( SCH_FIELD_VALIDATOR( true, REFERENCE ) );

    // initial focus should be on first editable field.
    m_textName->SetFocus();

    // What happens when user presses "Enter"? OK button!  OK?
    m_sdbSizerOK->SetDefault();

    // Now all widgets have the size fixed, call FinishDialogSettings
    FinishDialogSettings();
}


void DIALOG_LIB_NEW_COMPONENT::OnParentSymbolSelect( wxCommandEvent& event )
{
    syncControls( !m_comboInheritanceSelect->GetValue().IsEmpty() );
}


void DIALOG_LIB_NEW_COMPONENT::syncControls( bool aIsDerivedPart )
{
    m_staticTextDes->Enable( !aIsDerivedPart );
    m_textReference->Enable( !aIsDerivedPart );
    m_staticTextUnits->Enable( !aIsDerivedPart );
    m_spinPartCount->Enable( !aIsDerivedPart );
    m_checkLockItems->Enable( !aIsDerivedPart );
    m_checkHasConversion->Enable( !aIsDerivedPart );
    m_checkIsPowerSymbol->Enable( !aIsDerivedPart );
    m_staticText12->Enable( !aIsDerivedPart );
    m_spinPinTextPosition->Enable( !aIsDerivedPart );
    m_checkShowPinNumber->Enable( !aIsDerivedPart );
    m_checkShowPinName->Enable( !aIsDerivedPart );
    m_checkShowPinNameInside->Enable( !aIsDerivedPart );
}
