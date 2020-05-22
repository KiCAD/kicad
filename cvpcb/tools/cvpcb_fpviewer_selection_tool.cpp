/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2018-2019 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <functional>
using namespace std::placeholders;

#include <bitmaps.h>
#include <preview_items/ruler_item.h>
#include <tool/tool_event.h>
#include <tools/cvpcb_actions.h>
#include <tools/cvpcb_fpviewer_selection_tool.h>
#include <view/view.h>
#include <view/view_controls.h>

CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL() :
        TOOL_INTERACTIVE( "cvpcb.FootprintViewerInteractiveSelection" ),
        m_frame( nullptr )
{
}


bool CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::Init()
{
    getEditFrame<DISPLAY_FOOTPRINTS_FRAME>()->AddStandardSubMenus( m_menu );
    return true;
}


void CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::Reset( RESET_REASON aReason )
{
    m_frame = getEditFrame<DISPLAY_FOOTPRINTS_FRAME>();
}


int CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::Main( const TOOL_EVENT& aEvent )
{
    // Main loop: keep receiving events
    while( TOOL_EVENT* evt = Wait() )
    {
        if( m_frame->ToolStackIsEmpty() )
            m_frame->GetCanvas()->SetCurrentCursor( wxCURSOR_ARROW );

        // This is kind of hacky: activate RMB drag on any event.
        // There doesn't seem to be any other good way to tell when another tool
        // is canceled and control returns to the selection tool, except by the
        // fact that the selection tool starts to get events again.
        if( m_frame->IsCurrentTool( ACTIONS::selectionTool ) )
        {
            getViewControls()->SetAdditionalPanButtons( false, true );
        }

        // Disable RMB pan for other tools; they can re-enable if desired
        if( evt->IsActivate() )
        {
            getViewControls()->SetAdditionalPanButtons( false, false );
        }

        // single click? Select single object
        if( evt->IsClick( BUT_LEFT ) )
        {
            clearSelection();
        }

        // right click? if there is any object - show the context menu
        else if( evt->IsClick( BUT_RIGHT ) )
        {
            m_menu.ShowContextMenu( m_selection );
        }

        else if( evt->IsCancel() || evt->Action() == TA_UNDO_REDO_PRE )
        {
            clearSelection();
        }

        else
            evt->SetPassEvent();
    }

    return 0;
}


int CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::UpdateMenu( const TOOL_EVENT& aEvent )
{
    ACTION_MENU*      actionMenu      = aEvent.Parameter<ACTION_MENU*>();
    CONDITIONAL_MENU* conditionalMenu = dynamic_cast<CONDITIONAL_MENU*>( actionMenu );

    if( conditionalMenu )
        conditionalMenu->Evaluate( m_selection );

    if( actionMenu )
        actionMenu->UpdateAll();

    return 0;
}


void CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::setTransitions()
{
    Go( &CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::UpdateMenu, ACTIONS::updateMenu.MakeEvent() );
    Go( &CVPCB_FOOTPRINT_VIEWER_SELECTION_TOOL::Main,
            CVPCB_ACTIONS::selectionActivate.MakeEvent() );
}
