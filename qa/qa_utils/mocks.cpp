/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
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

#include <pgm_base.h>
#include <kiface_i.h>
#include <confirm.h>
#include <pcb_edit_frame.h>
#include <eda_dde.h>
#include <wx/file.h>
#include <wx/snglinst.h>
#include <wx/app.h>
#include <class_board.h>
#include <fp_lib_table.h>
#include <footprint_viewer_frame.h>
#include <footprint_wizard_frame.h>
#include <class_pcb_target.h>
#include <class_module.h>
#include <class_dimension.h>
#include <class_zone.h>
#include <tools/pcb_actions.h>
#include <router/router_tool.h>
#include <dialog_find.h>
#include <dialog_filter_selection.h>

FP_LIB_TABLE GFootprintTable;


#if 0

static struct IFACE : public KIFACE_I
{
    // Of course all are overloads, implementations of the KIFACE.

    IFACE( const char* aName, KIWAY::FACE_T aType ) :
        KIFACE_I( aName, aType )
    {}

    bool OnKifaceStart( PGM_BASE* aProgram, int aCtlBits ) override
    {
        return true;
    }

    void OnKifaceEnd() override {}

    wxWindow* CreateWindow( wxWindow* aParent, int aClassId, KIWAY* aKiway, int aCtlBits = 0 ) override
    {
        assert( false );
        return nullptr;
    }

    /**
     * Function IfaceOrAddress
     * return a pointer to the requested object.  The safest way to use this
     * is to retrieve a pointer to a static instance of an interface, similar to
     * how the KIFACE interface is exported.  But if you know what you are doing
     * use it to retrieve anything you want.
     *
     * @param aDataId identifies which object you want the address of.
     *
     * @return void* - and must be cast into the know type.
     */
    void* IfaceOrAddress( int aDataId ) override
    {
        return NULL;
    }
}
kiface( "pcb_test_frame", KIWAY::FACE_PCB );

static struct PGM_TEST_FRAME : public PGM_BASE
{
    bool OnPgmInit();

    void OnPgmExit()
    {
        Kiway.OnKiwayEnd();

        // Destroy everything in PGM_BASE, especially wxSingleInstanceCheckerImpl
        // earlier than wxApp and earlier than static destruction would.
        PGM_BASE::Destroy();
    }

    void MacOpenFile( const wxString& aFileName )   override
    {
        wxFileName filename( aFileName );

        if( filename.FileExists() )
        {
    #if 0
            // this pulls in EDA_DRAW_FRAME type info, which we don't want in
            // the single_top link image.
            KIWAY_PLAYER* frame = dynamic_cast<KIWAY_PLAYER*>( App().GetTopWindow() );
    #else
            KIWAY_PLAYER* frame = (KIWAY_PLAYER*) App().GetTopWindow();
    #endif

            if( frame )
                frame->OpenProjectFiles( std::vector<wxString>( 1, aFileName ) );
        }
    }
}
program;

PGM_BASE& Pgm()
{
    return program;
}


// Similar to PGM_BASE& Pgm(), but return nullptr when a *.ki_face
// is run from a python script, mot from a Kicad application
PGM_BASE* PgmOrNull()
{
    return nullptr; //&program;
}


KIFACE_I& Kiface()
{
    return kiface;
}
#endif

// FP_LIB_TABLE GFootprintTable;

DIALOG_FIND::DIALOG_FIND( PCB_BASE_FRAME* aParent ) : DIALOG_FIND_BASE( aParent )
{
    // these members are initialized to avoid warnings about non initialized vars
    m_frame = aParent;
    m_hitList.clear();
    m_it = m_hitList.begin();
    m_upToDate = false;
}

void DIALOG_FIND::onFindNextClick( wxCommandEvent& aEvent )
{
}

void DIALOG_FIND::onFindPreviousClick( wxCommandEvent& aEvent )
{
}

void DIALOG_FIND::onSearchAgainClick( wxCommandEvent& aEvent )
{
}

void DIALOG_FIND::onTextEnter( wxCommandEvent& event )
{
}

void DIALOG_FIND::onClose( wxCommandEvent& aEvent )
{
}


DIALOG_FIND_BASE::DIALOG_FIND_BASE( wxWindow* parent, wxWindowID id, const wxString& title,
                                    const wxPoint& pos, const wxSize& size, long style ) :
        DIALOG_SHIM( parent, id, title, pos, size, style )
{
    // these members are initialized only to avoid warnings about non initialized vars
    searchStringLabel = nullptr;
    m_searchCombo = nullptr;
    m_matchCase = nullptr;
    m_matchWords = nullptr;
    m_wildcards = nullptr;
    m_wrap = nullptr;
    m_includeValues = nullptr;
    m_includeReferences = nullptr;
    m_includeTexts = nullptr;
    m_includeMarkers = nullptr;
    m_includeVias = nullptr;
    m_findNext = nullptr;
    m_findPrevious = nullptr;
    m_searchAgain = nullptr;
    m_closeButton = nullptr;
    m_status = nullptr;
}


DIALOG_FIND_BASE::~DIALOG_FIND_BASE()
{
}


MODULE* PCB_BASE_FRAME::GetFootprintFromBoardByReference()
{
    return nullptr;
}


DIALOG_FILTER_SELECTION_BASE::DIALOG_FILTER_SELECTION_BASE( wxWindow* parent, wxWindowID id,
                                                            const wxString& title,
                                                            const wxPoint& pos, const wxSize& size,
                                                            long style ) :
        DIALOG_SHIM( parent, id, title, pos, size, style )
{
    // these members are initialized only to avoid warnings about non initialized vars
    m_Include_Modules = nullptr;
    m_Include_PcbTextes = nullptr;
    m_IncludeLockedModules = nullptr;
    m_Include_Draw_Items = nullptr;
    m_Include_Tracks = nullptr;
    m_Include_Vias = nullptr;
    m_Include_Edges_Items = nullptr;
    m_Include_Zones = nullptr;
    m_sdbSizer1 = nullptr;
    m_staticLine = nullptr;
    m_sdbSizer1OK = nullptr;
    m_sdbSizer1Cancel = nullptr;
}


DIALOG_FILTER_SELECTION_BASE::~DIALOG_FILTER_SELECTION_BASE()
{
}


DIALOG_FILTER_SELECTION::DIALOG_FILTER_SELECTION( PCB_BASE_FRAME* aParent, OPTIONS& aOptions ) :
        DIALOG_FILTER_SELECTION_BASE( aParent ),
        m_options( aOptions )
{
    // silence another compiler warning about m_options not being used
    if( m_options.includeModules )
    {
    }
}


void DIALOG_FILTER_SELECTION::checkBoxClicked( wxCommandEvent& aEvent )
{
}


void DIALOG_FILTER_SELECTION::ExecuteCommand( wxCommandEvent& event )
{
}


void ROUTER_TOOL::NeighboringSegmentFilter( const VECTOR2I&, GENERAL_COLLECTOR& )
{
}


static const int viewer3dSchemaVersion = 0;

#include "3d_viewer/3d_viewer_settings.h"


EDA_3D_VIEWER_SETTINGS::EDA_3D_VIEWER_SETTINGS()
        : APP_SETTINGS_BASE( "3d_viewer", viewer3dSchemaVersion ),
          m_Render(),
          m_Camera()
{
}


bool EDA_3D_VIEWER_SETTINGS::MigrateFromLegacy( wxConfigBase* aCfg )
{
  return false;
}

#include "3d_viewer/eda_3d_viewer.h"
#include <3d_viewer/3d_viewer_settings.h>
#include <3d-viewer/3d_viewer_id.h>

/**
 * Flag to enable 3D viewer main frame window debug tracing.
 *
 * Use "KI_TRACE_EDA_3D_VIEWER" to enable.
 *
 * @ingroup trace_env_vars
 */
const wxChar * EDA_3D_VIEWER::m_logTrace = wxT( "KI_TRACE_EDA_3D_VIEWER" );


BEGIN_EVENT_TABLE( EDA_3D_VIEWER, EDA_BASE_FRAME )

    EVT_ACTIVATE( EDA_3D_VIEWER::OnActivate )
    EVT_SET_FOCUS( EDA_3D_VIEWER::OnSetFocus )

    EVT_TOOL_RANGE( ID_START_COMMAND_3D, ID_MENU_COMMAND_END,
                    EDA_3D_VIEWER::Process_Special_Functions )

    EVT_TOOL( ID_TOOL_SET_VISIBLE_ITEMS, EDA_3D_VIEWER::Install3DViewOptionDialog )

    EVT_MENU( wxID_CLOSE, EDA_3D_VIEWER::Exit3DFrame )
    EVT_MENU( ID_RENDER_CURRENT_VIEW, EDA_3D_VIEWER::OnRenderEngineSelection )
    EVT_MENU( ID_DISABLE_RAY_TRACING, EDA_3D_VIEWER::OnDisableRayTracing )

    EVT_CLOSE( EDA_3D_VIEWER::OnCloseWindow )
END_EVENT_TABLE()


EDA_3D_VIEWER::EDA_3D_VIEWER( KIWAY *aKiway, PCB_BASE_FRAME *aParent, const wxString &aTitle,
                              long style ) :
        KIWAY_PLAYER( aKiway, aParent, FRAME_PCB_DISPLAY3D, aTitle, wxDefaultPosition,
                      wxDefaultSize, style, QUALIFIED_VIEWER3D_FRAMENAME( aParent ) ),
        m_mainToolBar( nullptr ),
        m_canvas( nullptr ),
        m_currentCamera( m_trackBallCamera ),
        m_trackBallCamera( RANGE_SCALE_3D )
{

}


EDA_3D_VIEWER::~EDA_3D_VIEWER()
{

}


void EDA_3D_VIEWER::setupUIConditions()
{

}


void EDA_3D_VIEWER::ReloadRequest()
{

}


void EDA_3D_VIEWER::NewDisplay( bool aForceImmediateRedraw )
{

}


void EDA_3D_VIEWER::Exit3DFrame( wxCommandEvent &event )
{

}


void EDA_3D_VIEWER::OnCloseWindow( wxCloseEvent &event )
{

}


void EDA_3D_VIEWER::Process_Special_Functions( wxCommandEvent &event )
{

}


void EDA_3D_VIEWER::OnRenderEngineSelection( wxCommandEvent &event )
{

}


void EDA_3D_VIEWER::OnDisableRayTracing( wxCommandEvent& aEvent )
{

}


void EDA_3D_VIEWER::OnActivate( wxActivateEvent &event )
{

}


void EDA_3D_VIEWER::OnSetFocus(wxFocusEvent &event)
{

}


void EDA_3D_VIEWER::LoadSettings( APP_SETTINGS_BASE *aCfg )
{

}


void EDA_3D_VIEWER::SaveSettings( APP_SETTINGS_BASE *aCfg )
{

}


void EDA_3D_VIEWER::SynchroniseColoursWithBoard()
{

}


void EDA_3D_VIEWER::CommonSettingsChanged( bool aEnvVarsChanged, bool aTextVarsChanged )
{

}


void EDA_3D_VIEWER::takeScreenshot( wxCommandEvent& event )
{


}


void EDA_3D_VIEWER::RenderEngineChanged()
{

}


bool EDA_3D_VIEWER::Set3DColorFromUser( SFVEC4F &aColor, const wxString& aTitle,
                                        CUSTOM_COLORS_LIST* aPredefinedColors,
                                        bool aAllowOpacityControl,
                                        KIGFX::COLOR4D aDefaultColor )
{

    return true;
}


bool EDA_3D_VIEWER::Set3DSilkScreenColorFromUser()
{
    return false;
}


bool EDA_3D_VIEWER::Set3DSolderMaskColorFromUser()
{
    return false;
}


void EDA_3D_VIEWER::Redraw(){};

bool EDA_3D_VIEWER::Set3DCopperColorFromUser(){ return false; }
bool EDA_3D_VIEWER::Set3DBoardBodyColorFromUser() { return false; }
bool EDA_3D_VIEWER::Set3DSolderPasteColorFromUser() { return false; }
void EDA_3D_VIEWER::loadCommonSettings() { }
void EDA_3D_VIEWER::Install3DViewOptionDialog( wxCommandEvent& event ) { };

#include <tools/selection_tool.h>


/**
 * Private implementation of firewalled private data
 */
class SELECTION_TOOL::PRIV
{
public:
    DIALOG_FILTER_SELECTION::OPTIONS m_filterOpts;
};


SELECTION_TOOL::SELECTION_TOOL() :
        PCB_TOOL_BASE( "pcbnew.InteractiveSelection" ),
        m_frame( NULL ),
        m_additive( false ),
        m_subtractive( false ),
        m_exclusive_or( false ),
        m_multiple( false ),
        m_skip_heuristics( false ),
        m_locked( true ),
        m_enteredGroup( NULL ),
        m_priv( nullptr )
{

}


SELECTION_TOOL::~SELECTION_TOOL()
{
}


bool SELECTION_TOOL::Init()
{

    return true;
}


void SELECTION_TOOL::Reset( RESET_REASON aReason )
{

}


int SELECTION_TOOL::Main( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::EnterGroup()
{

}


void SELECTION_TOOL::ExitGroup( bool aSelectGroup )
{

}


PCBNEW_SELECTION& SELECTION_TOOL::GetSelection()
{
    return m_selection;
}


PCBNEW_SELECTION& SELECTION_TOOL::RequestSelection( CLIENT_SELECTION_FILTER aClientFilter,
                                                    std::vector<BOARD_ITEM*>* aFiltered,
                                                    bool aConfirmLockedItems )
{

    return m_selection;
}


const GENERAL_COLLECTORS_GUIDE SELECTION_TOOL::getCollectorsGuide() const
{
    return GENERAL_COLLECTORS_GUIDE( LSET(), PCB_LAYER_ID::UNDEFINED_LAYER, nullptr );
}


bool SELECTION_TOOL::selectPoint( const VECTOR2I& aWhere, bool aOnDrag,
                                  bool* aSelectionCancelledFlag,
                                  CLIENT_SELECTION_FILTER aClientFilter )
{


    return false;
}


bool SELECTION_TOOL::selectCursor( bool aForceSelect, CLIENT_SELECTION_FILTER aClientFilter )
{

    return false;
}


bool SELECTION_TOOL::selectMultiple()
{

    return false;
}


SELECTION_LOCK_FLAGS SELECTION_TOOL::CheckLock()
{

    return SELECTION_UNLOCKED;
}


int SELECTION_TOOL::CursorSelection( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::ClearSelection( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::SelectItems( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::SelectItem( const TOOL_EVENT& aEvent )
{
    return 0;
}


int SELECTION_TOOL::SelectAll( const TOOL_EVENT& aEvent )
{


    return 0;
}


void SELECTION_TOOL::AddItemToSel( BOARD_ITEM* aItem, bool aQuietMode )
{

}


int SELECTION_TOOL::UnselectItems( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::UnselectItem( const TOOL_EVENT& aEvent )
{
    return 0;
}


void SELECTION_TOOL::RemoveItemFromSel( BOARD_ITEM* aItem, bool aQuietMode )
{

}


void SELECTION_TOOL::BrightenItem( BOARD_ITEM* aItem )
{
}


void SELECTION_TOOL::UnbrightenItem( BOARD_ITEM* aItem )
{
}




int SELECTION_TOOL::expandConnection( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::selectConnectedTracks( BOARD_CONNECTED_ITEM& aStartItem,
                                            STOP_CONDITION aStopCondition )
{

}


void SELECTION_TOOL::selectAllItemsOnNet( int aNetCode, bool aSelect )
{

}


int SELECTION_TOOL::selectNet( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::selectAllItemsOnSheet( wxString& aSheetPath )
{

}


void SELECTION_TOOL::zoomFitSelection()
{

}


int SELECTION_TOOL::selectSheetContents( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::selectSameSheet( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::findCallback( BOARD_ITEM* aItem )
{

}


int SELECTION_TOOL::find( const TOOL_EVENT& aEvent )
{

    return 0;
}


/**
 * Function itemIsIncludedByFilter()
 *
 * Determine if an item is included by the filter specified
 *
 * @return true if aItem should be selected by this filter (i..e not filtered out)
 */
static bool itemIsIncludedByFilter( const BOARD_ITEM& aItem, const BOARD& aBoard,
                                    const DIALOG_FILTER_SELECTION::OPTIONS& aFilterOptions )
{


    return false;
}


int SELECTION_TOOL::filterSelection( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::FilterCollectedItems( GENERAL_COLLECTOR& aCollector )
{

}


bool SELECTION_TOOL::itemPassesFilter( BOARD_ITEM* aItem )
{


    return true;
}


void SELECTION_TOOL::ClearSelection( bool aQuietMode )
{

}


void SELECTION_TOOL::RebuildSelection()
{

}


int SELECTION_TOOL::SelectionMenu( const TOOL_EVENT& aEvent )
{

    return 0;
}


bool SELECTION_TOOL::doSelectionMenu( GENERAL_COLLECTOR* aCollector, const wxString& aTitle )
{
    return false;
}


BOARD_ITEM* SELECTION_TOOL::pickSmallestComponent( GENERAL_COLLECTOR* aCollector )
{
    return nullptr;
}


bool SELECTION_TOOL::Selectable( const BOARD_ITEM* aItem, bool checkVisibilityOnly ) const
{
    return false;
}


void SELECTION_TOOL::select( BOARD_ITEM* aItem )
{

}


void SELECTION_TOOL::unselect( BOARD_ITEM* aItem )
{

}

void SELECTION_TOOL::highlight( BOARD_ITEM* aItem, int aMode, PCBNEW_SELECTION* aGroup )
{

}

void SELECTION_TOOL::highlightInternal( BOARD_ITEM* aItem, int aMode, PCBNEW_SELECTION* aGroup, bool isChild )
{

}


void SELECTION_TOOL::unhighlight( BOARD_ITEM* aItem, int aMode, PCBNEW_SELECTION* aGroup )
{

}


void SELECTION_TOOL::unhighlightInternal( BOARD_ITEM* aItem, int aMode, PCBNEW_SELECTION* aGroup, bool isChild )
{

}


bool SELECTION_TOOL::selectionContains( const VECTOR2I& aPoint ) const
{


    return false;
}

void SELECTION_TOOL::GuessSelectionCandidates( GENERAL_COLLECTOR& aCollector,
                                               const VECTOR2I& aWhere ) const
{

}


void SELECTION_TOOL::FilterCollectorForGroups( GENERAL_COLLECTOR& aCollector ) const
{

}


int SELECTION_TOOL::updateSelection( const TOOL_EVENT& aEvent )
{

    return 0;
}


int SELECTION_TOOL::UpdateMenu( const TOOL_EVENT& aEvent )
{

    return 0;
}


void SELECTION_TOOL::setTransitions()
{}

void PCB_TOOL_BASE::doInteractiveItemPlacement( const std::string& aTool,
                                                INTERACTIVE_PLACER_BASE* aPlacer,
                                                const wxString& aCommitMessage, int aOptions )
{
}


bool PCB_TOOL_BASE::Init()
{
    return true;
}


void PCB_TOOL_BASE::Reset( RESET_REASON aReason )
{
}


void PCB_TOOL_BASE::setTransitions()
{
}


const PCB_DISPLAY_OPTIONS& PCB_TOOL_BASE::displayOptions() const
{
    static PCB_DISPLAY_OPTIONS disp;

    return disp;
}

PCB_DRAW_PANEL_GAL* PCB_TOOL_BASE::canvas() const
{
    return nullptr;
}


const PCBNEW_SELECTION& PCB_TOOL_BASE::selection() const
{
    static PCBNEW_SELECTION sel;

    return sel;
}


PCBNEW_SELECTION& PCB_TOOL_BASE::selection()
{
    static PCBNEW_SELECTION sel;

    return sel;
}


EDA_ITEM* PCBNEW_SELECTION::GetTopLeftItem( bool onlyModules ) const
{
   return nullptr;
}


const KIGFX::VIEW_GROUP::ITEMS PCBNEW_SELECTION::updateDrawList() const
{
    std::vector<VIEW_ITEM*> items;

   return items;
}


const LSET PCBNEW_SELECTION::GetSelectionLayers()
{
  return LSET();
}

