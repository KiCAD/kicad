#ifndef PCBNEW_ID_H_
#define PCBNEW_ID_H_

#include <id.h>

/**
 * Command IDs for the printed circuit board editor.
 *
 * Please add IDs that are unique to the printed circuit board editor (Pcbnew)
 * here and not in the global id.h file.  This will prevent the entire project
 * from being rebuilt when adding new commands to the Pcbnew.
 */

enum pcbnew_ids
{
    ID_MAIN_MENUBAR = ID_END_LIST,
    ID_MICROWAVE_V_TOOLBAR,
    ID_COPY_BOARD_AS,
    ID_IMPORT_NON_KICAD_BOARD,

    // Right vertical tool bar command IDs.
    ID_PCB_HIGHLIGHT_BUTT,
    ID_LOCAL_RATSNEST_BUTT,
    ID_PCB_MODULE_BUTT,
    ID_TRACK_BUTT,
    ID_PCB_ZONES_BUTT,
    ID_PCB_DRAW_VIA_BUTT,
    ID_PCB_KEEPOUT_BUTT,
    ID_PCB_ADD_LINE_BUTT,
    ID_PCB_ADD_POLYGON_BUTT,
    ID_PCB_CIRCLE_BUTT,
    ID_PCB_ARC_BUTT,
    ID_PCB_ADD_TEXT_BUTT,
    ID_PCB_DIMENSION_BUTT,
    ID_PCB_TARGET_BUTT,
    ID_PCB_DELETE_ITEM_BUTT,
    ID_PCB_PLACE_OFFSET_COORD_BUTT,
    ID_PCB_PLACE_GRID_COORD_BUTT,
    ID_PCB_MEASUREMENT_TOOL,

    // Tracks and vias sizes general options
    ID_AUX_TOOLBAR_PCB_VIA_SIZE,
    ID_AUX_TOOLBAR_PCB_TRACK_WIDTH,
    ID_AUX_TOOLBAR_PCB_SELECT_AUTO_WIDTH,
    ID_POPUP_PCB_SELECT_WIDTH_START_RANGE,
    ID_POPUP_PCB_SELECT_CUSTOM_WIDTH,
    ID_POPUP_PCB_SELECT_AUTO_WIDTH,
    ID_POPUP_PCB_SELECT_USE_NETCLASS_VALUES,
    ID_POPUP_PCB_SELECT_WIDTH1,
    ID_POPUP_PCB_SELECT_WIDTH2,
    ID_POPUP_PCB_SELECT_WIDTH3,
    ID_POPUP_PCB_SELECT_WIDTH4,
    ID_POPUP_PCB_SELECT_WIDTH5,
    ID_POPUP_PCB_SELECT_WIDTH6,
    ID_POPUP_PCB_SELECT_WIDTH7,
    ID_POPUP_PCB_SELECT_WIDTH8,
    ID_POPUP_PCB_SELECT_WIDTH9,
    ID_POPUP_PCB_SELECT_WIDTH10,
    ID_POPUP_PCB_SELECT_WIDTH11,
    ID_POPUP_PCB_SELECT_WIDTH12,
    ID_POPUP_PCB_SELECT_WIDTH13,
    ID_POPUP_PCB_SELECT_WIDTH14,
    ID_POPUP_PCB_SELECT_WIDTH15,
    ID_POPUP_PCB_SELECT_WIDTH16,
    ID_POPUP_PCB_SELECT_VIASIZE1,
    ID_POPUP_PCB_SELECT_VIASIZE2,
    ID_POPUP_PCB_SELECT_VIASIZE3,
    ID_POPUP_PCB_SELECT_VIASIZE4,
    ID_POPUP_PCB_SELECT_VIASIZE5,
    ID_POPUP_PCB_SELECT_VIASIZE6,
    ID_POPUP_PCB_SELECT_VIASIZE7,
    ID_POPUP_PCB_SELECT_VIASIZE8,
    ID_POPUP_PCB_SELECT_VIASIZE9,
    ID_POPUP_PCB_SELECT_VIASIZE10,
    ID_POPUP_PCB_SELECT_VIASIZE11,
    ID_POPUP_PCB_SELECT_VIASIZE12,
    ID_POPUP_PCB_SELECT_VIASIZE13,
    ID_POPUP_PCB_SELECT_VIASIZE14,
    ID_POPUP_PCB_SELECT_VIASIZE15,
    ID_POPUP_PCB_SELECT_VIASIZE16,
    ID_POPUP_PCB_SELECT_CUSTOM_DIFFPAIR,
    ID_POPUP_PCB_SELECT_USE_NETCLASS_DIFFPAIR,
    ID_POPUP_PCB_SELECT_DIFFPAIR1,
    ID_POPUP_PCB_SELECT_DIFFPAIR2,
    ID_POPUP_PCB_SELECT_DIFFPAIR3,
    ID_POPUP_PCB_SELECT_DIFFPAIR4,
    ID_POPUP_PCB_SELECT_DIFFPAIR5,
    ID_POPUP_PCB_SELECT_DIFFPAIR6,
    ID_POPUP_PCB_SELECT_DIFFPAIR7,
    ID_POPUP_PCB_SELECT_DIFFPAIR8,
    ID_POPUP_PCB_SELECT_DIFFPAIR9,
    ID_POPUP_PCB_SELECT_DIFFPAIR10,
    ID_POPUP_PCB_SELECT_DIFFPAIR11,
    ID_POPUP_PCB_SELECT_DIFFPAIR12,
    ID_POPUP_PCB_SELECT_DIFFPAIR13,
    ID_POPUP_PCB_SELECT_DIFFPAIR14,
    ID_POPUP_PCB_SELECT_DIFFPAIR15,
    ID_POPUP_PCB_SELECT_DIFFPAIR16,
    ID_POPUP_PCB_SELECT_WIDTH_END_RANGE,

    ID_MENU_READ_BOARD_BACKUP_FILE,
    ID_MENU_RECOVER_BOARD_AUTOSAVE,
    ID_MENU_ARCHIVE_MODULES_IN_LIBRARY,
    ID_MENU_CREATE_LIBRARY_AND_ARCHIVE_MODULES,

    ID_GEN_EXPORT_FILE_IDF3,
    ID_GEN_EXPORT_FILE_VRML,
    ID_GEN_EXPORT_FILE_STEP,
    ID_GEN_EXPORT_FILE_HYPERLYNX,
    ID_GEN_EXPORT_FILE_GENCADFORMAT,
    ID_GEN_IMPORT_GRAPHICS_FILE,

    ID_TOOLBARH_PCB_ACTION_PLUGIN,
    ID_TOOLBARH_PCB_ACTION_PLUGIN_REFRESH,

    ID_AUX_TOOLBAR_PCB_SELECT_LAYER_PAIR,

    ID_PCB_GEN_CMP_FILE,
    ID_PCB_GEN_BOM_FILE_FROM_BOARD,
    ID_PCB_3DSHAPELIB_WIZARD,

    ID_TOOLBARH_PCB_SELECT_LAYER,

    // ID used in module editor:
    ID_MODEDIT_CHECK,
    ID_MODEDIT_SAVE,
    ID_MODEDIT_SAVE_AS,
    ID_MODEDIT_SAVE_PNG,
    ID_MODEDIT_NEW_MODULE,
    ID_MODEDIT_NEW_MODULE_FROM_WIZARD,
    ID_MODEDIT_LOAD_MODULE_FROM_BOARD,

    ID_MODVIEW_LIB_FILTER,
    ID_MODVIEW_LIB_LIST,
    ID_MODVIEW_FOOTPRINT_FILTER,
    ID_MODVIEW_FOOTPRINT_LIST,
    ID_MODVIEW_OPTIONS,
    ID_MODVIEW_PREVIOUS,
    ID_MODVIEW_NEXT,

    ID_FOOTPRINT_WIZARD_NEXT,
    ID_FOOTPRINT_WIZARD_PREVIOUS,
    ID_FOOTPRINT_WIZARD_DONE,
    ID_FOOTPRINT_WIZARD_PAGE_LIST,
    ID_FOOTPRINT_WIZARD_PARAMETER_LIST,
    ID_FOOTPRINT_WIZARD_SELECT_WIZARD,
    ID_FOOTPRINT_WIZARD_RESET_TO_DEFAULT,

    ID_ADD_FOOTPRINT_TO_BOARD,

    ID_PANEL_FPLIB_ADD_KICADMOD,
    ID_PANEL_FPLIB_ADD_EAGLE6,
    ID_PANEL_FPLIB_ADD_KICADLEGACY,
    ID_PANEL_FPLIB_ADD_GEDA,

    ID_PCBNEW_END_LIST
};

#endif  // PCBNEW_ID_H_
