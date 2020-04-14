/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004-2020 KiCad Developers, see AUTHORS.txt for contributors.
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
 * @file lib_text.cpp
 */

#include <fctsys.h>
#include <gr_basic.h>
#include <macros.h>
#include <sch_draw_panel.h>
#include <plotter.h>
#include <gr_text.h>
#include <trigo.h>
#include <base_units.h>
#include <msgpanel.h>
#include <bitmaps.h>

#include <lib_item.h>
#include <general.h>
#include <transform.h>
#include <settings/color_settings.h>
#include <lib_text.h>
#include <default_values.h>    // For some default values


LIB_TEXT::LIB_TEXT( LIB_PART* aParent, int aMarkupFlags ) :
    LIB_ITEM( LIB_TEXT_T, aParent ),
    EDA_TEXT( wxEmptyString, aMarkupFlags )
{
    SetTextSize( wxSize( Mils2iu( DEFAULT_TEXT_SIZE ), Mils2iu( DEFAULT_TEXT_SIZE ) ) );
}


void LIB_TEXT::ViewGetLayers( int aLayers[], int& aCount ) const
{
    aCount      = 2;
    aLayers[0]  = LAYER_DEVICE;
    aLayers[1]  = LAYER_SELECTION_SHADOWS;
}


bool LIB_TEXT::HitTest( const wxPoint& aPosition, int aAccuracy ) const
{
    EDA_TEXT tmp_text( *this );
    tmp_text.SetTextPos( DefaultTransform.TransformCoordinate( GetTextPos() ) );

    /* The text orientation may need to be flipped if the
     * transformation matrix causes xy axes to be flipped.
     * this simple algo works only for schematic matrix (rot 90 or/and mirror)
     */
    bool t1 = ( DefaultTransform.x1 != 0 ) ^ ( GetTextAngle() != 0 );

    tmp_text.SetTextAngle( t1 ? TEXT_ANGLE_HORIZ : TEXT_ANGLE_VERT );
    return tmp_text.TextHitTest( aPosition, aAccuracy );
}


EDA_ITEM* LIB_TEXT::Clone() const
{
    LIB_TEXT* newitem = new LIB_TEXT( nullptr, GetTextMarkupFlags() );

    newitem->m_Unit      = m_Unit;
    newitem->m_Convert   = m_Convert;
    newitem->m_Flags     = m_Flags;

    newitem->SetText( GetText() );
    newitem->SetEffects( *this );

    return newitem;
}


int LIB_TEXT::compare( const LIB_ITEM& aOther, LIB_ITEM::COMPARE_FLAGS aCompareFlags ) const
{
    wxASSERT( aOther.Type() == LIB_TEXT_T );

    int retv = LIB_ITEM::compare( aOther, aCompareFlags );

    if( retv )
        return retv;

    const LIB_TEXT* tmp = ( LIB_TEXT* ) &aOther;

    int result = GetText().CmpNoCase( tmp->GetText() );

    if( result != 0 )
        return result;

    if( GetTextPos().x != tmp->GetTextPos().x )
        return GetTextPos().x - tmp->GetTextPos().x;

    if( GetTextPos().y != tmp->GetTextPos().y )
        return GetTextPos().y - tmp->GetTextPos().y;

    if( GetTextWidth() != tmp->GetTextWidth() )
        return GetTextWidth() - tmp->GetTextWidth();

    if( GetTextHeight() != tmp->GetTextHeight() )
        return GetTextHeight() - tmp->GetTextHeight();

    return 0;
}


void LIB_TEXT::Offset( const wxPoint& aOffset )
{
    EDA_TEXT::Offset( aOffset );
}


void LIB_TEXT::MoveTo( const wxPoint& newPosition )
{
    SetTextPos( newPosition );
}


void LIB_TEXT::NormalizeJustification( bool inverse )
{
    wxPoint  delta( 0, 0 );
    EDA_RECT bbox = GetTextBox();

    if( GetTextAngle() == 0.0 )
    {
        if( GetHorizJustify() == GR_TEXT_HJUSTIFY_LEFT )
            delta.x = bbox.GetWidth() / 2;
        else if( GetHorizJustify() == GR_TEXT_HJUSTIFY_RIGHT )
            delta.x = - bbox.GetWidth() / 2;

        if( GetVertJustify() == GR_TEXT_VJUSTIFY_TOP )
            delta.y = - bbox.GetHeight() / 2;
        else if( GetVertJustify() == GR_TEXT_VJUSTIFY_BOTTOM )
            delta.y = bbox.GetHeight() / 2;
    }
    else
    {
        if( GetHorizJustify() == GR_TEXT_HJUSTIFY_LEFT )
            delta.y = bbox.GetWidth() / 2;
        else if( GetHorizJustify() == GR_TEXT_HJUSTIFY_RIGHT )
            delta.y = - bbox.GetWidth() / 2;

        if( GetVertJustify() == GR_TEXT_VJUSTIFY_TOP )
            delta.x = + bbox.GetHeight() / 2;
        else if( GetVertJustify() == GR_TEXT_VJUSTIFY_BOTTOM )
            delta.x = - bbox.GetHeight() / 2;
    }

    if( inverse )
        SetTextPos( GetTextPos() - delta );
    else
        SetTextPos( GetTextPos() + delta );
}


void LIB_TEXT::MirrorHorizontal( const wxPoint& center )
{
    NormalizeJustification( false );
    int x = GetTextPos().x;

    x -= center.x;
    x *= -1;
    x += center.x;

    if( GetTextAngle() == 0.0 )
    {
        if( GetHorizJustify() == GR_TEXT_HJUSTIFY_LEFT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_RIGHT );
        else if( GetHorizJustify() == GR_TEXT_HJUSTIFY_RIGHT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_LEFT );
    }
    else
    {
        if( GetVertJustify() == GR_TEXT_VJUSTIFY_TOP )
            SetVertJustify( GR_TEXT_VJUSTIFY_BOTTOM );
        else if( GetVertJustify() == GR_TEXT_VJUSTIFY_BOTTOM )
            SetVertJustify( GR_TEXT_VJUSTIFY_TOP );
    }

    SetTextX( x );
    NormalizeJustification( true );
}


void LIB_TEXT::MirrorVertical( const wxPoint& center )
{
    NormalizeJustification( false );
    int y = GetTextPos().y;

    y -= center.y;
    y *= -1;
    y += center.y;

    if( GetTextAngle() == 0.0 )
    {
        if( GetVertJustify() == GR_TEXT_VJUSTIFY_TOP )
            SetVertJustify( GR_TEXT_VJUSTIFY_BOTTOM );
        else if( GetVertJustify() == GR_TEXT_VJUSTIFY_BOTTOM )
            SetVertJustify( GR_TEXT_VJUSTIFY_TOP );
    }
    else
    {
        if( GetHorizJustify() == GR_TEXT_HJUSTIFY_LEFT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_RIGHT );
        else if( GetHorizJustify() == GR_TEXT_HJUSTIFY_RIGHT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_LEFT );
    }

    SetTextY( y );
    NormalizeJustification( true );
}


void LIB_TEXT::Rotate( const wxPoint& center, bool aRotateCCW )
{
    NormalizeJustification( false );
    int rot_angle = aRotateCCW ? -900 : 900;

    wxPoint pt = GetTextPos();
    RotatePoint( &pt, center, rot_angle );
    SetTextPos( pt );

    if( GetTextAngle() == 0.0 )
    {
        SetTextAngle( 900 );
    }
    else
    {
        // 180º of rotation is a mirror

        if( GetHorizJustify() == GR_TEXT_HJUSTIFY_LEFT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_RIGHT );
        else if( GetHorizJustify() == GR_TEXT_HJUSTIFY_RIGHT )
            SetHorizJustify( GR_TEXT_HJUSTIFY_LEFT );

        if( GetVertJustify() == GR_TEXT_VJUSTIFY_TOP )
            SetVertJustify( GR_TEXT_VJUSTIFY_BOTTOM );
        else if( GetVertJustify() == GR_TEXT_VJUSTIFY_BOTTOM )
            SetVertJustify( GR_TEXT_VJUSTIFY_TOP );

        SetTextAngle( 0 );
    }

    NormalizeJustification( true );
}


void LIB_TEXT::Plot( PLOTTER* plotter, const wxPoint& offset, bool fill,
                     const TRANSFORM& aTransform )
{
    wxASSERT( plotter != NULL );

    EDA_RECT bBox = GetBoundingBox();
    // convert coordinates from draw Y axis to libedit Y axis
    bBox.RevertYAxis();
    wxPoint txtpos = bBox.Centre();

    /* The text orientation may need to be flipped if the
     * transformation matrix causes xy axes to be flipped. */
    int t1  = ( aTransform.x1 != 0 ) ^ ( GetTextAngle() != 0 );
    wxPoint pos = aTransform.TransformCoordinate( txtpos ) + offset;

    // Get color
    COLOR4D color;

    if( plotter->GetColorMode() )       // Used normal color or selected color
        color = plotter->RenderSettings()->GetLayerColor( LAYER_DEVICE );
    else
        color = COLOR4D::BLACK;

    int penWidth = std::max( GetEffectiveTextPenWidth(),
                             plotter->RenderSettings()->GetDefaultPenWidth() );

    // NOTE: do NOT use m_textMarkupFlags; those are from the library, not the schematic

    plotter->Text( pos, color, GetText(), t1 ? TEXT_ANGLE_HORIZ : TEXT_ANGLE_VERT, GetTextSize(),
                   GR_TEXT_HJUSTIFY_CENTER, GR_TEXT_VJUSTIFY_CENTER, penWidth, IsItalic(),
                   IsBold(), plotter->GetTextMarkupFlags() );
}


int LIB_TEXT::GetPenWidth() const
{
    return GetEffectiveTextPenWidth();
}


void LIB_TEXT::print( RENDER_SETTINGS* aSettings, const wxPoint& aOffset, void* aData,
                      const TRANSFORM& aTransform )
{
    wxDC*   DC = aSettings->GetPrintDC();
    COLOR4D color = aSettings->GetLayerColor( LAYER_DEVICE );
    int     penWidth = std::max( GetEffectiveTextPenWidth(), aSettings->GetDefaultPenWidth() );

    /* Calculate the text orientation, according to the component
     * orientation/mirror (needed when draw text in schematic)
     */
    int orient = (int) GetTextAngle();

    if( aTransform.y1 )  // Rotate component 90 degrees.
    {
        if( orient == TEXT_ANGLE_HORIZ )
            orient = TEXT_ANGLE_VERT;
        else
            orient = TEXT_ANGLE_HORIZ;
    }

    /* Calculate the text justification, according to the component
     * orientation/mirror this is a bit complicated due to cumulative
     * calculations:
     * - numerous cases (mirrored or not, rotation)
     * - the DrawGraphicText function recalculate also H and H justifications
     *      according to the text orientation.
     * - When a component is mirrored, the text is not mirrored and
     *   justifications are complicated to calculate
     * so the more easily way is to use no justifications ( Centered text )
     * and use GetBoundaryBox to know the text coordinate considered as centered
    */
    EDA_RECT bBox = GetBoundingBox();

    // convert coordinates from draw Y axis to libedit Y axis:
    bBox.RevertYAxis();
    wxPoint txtpos = bBox.Centre();

    // Calculate pos according to mirror/rotation.
    txtpos = aTransform.TransformCoordinate( txtpos ) + aOffset;

    GRText( DC, txtpos, color, GetShownText(), orient, GetTextSize(), GR_TEXT_HJUSTIFY_CENTER,
            GR_TEXT_VJUSTIFY_CENTER, penWidth, IsItalic(), IsBold(), m_textMarkupFlags );
}


void LIB_TEXT::GetMsgPanelInfo( EDA_UNITS aUnits, MSG_PANEL_ITEMS& aList )
{
    LIB_ITEM::GetMsgPanelInfo( aUnits, aList );

    wxString msg = MessageTextFromValue( aUnits, GetTextThickness(), true );
    aList.push_back( MSG_PANEL_ITEM( _( "Line Width" ), msg, BLUE ) );
}


const EDA_RECT LIB_TEXT::GetBoundingBox() const
{
    /* Y coordinates for LIB_ITEMS are bottom to top, so we must invert the Y position when
     * calling GetTextBox() that works using top to bottom Y axis orientation.
     */
    EDA_RECT rect = GetTextBox( -1, true );
    rect.RevertYAxis();

    // We are using now a bottom to top Y axis.
    wxPoint orig = rect.GetOrigin();
    wxPoint end  = rect.GetEnd();

    RotatePoint( &orig, GetTextPos(), -GetTextAngle() );
    RotatePoint( &end,  GetTextPos(), -GetTextAngle() );

    rect.SetOrigin( orig );
    rect.SetEnd( end );

    // We are using now a top to bottom Y axis:
    rect.RevertYAxis();

    return rect;
}


wxString LIB_TEXT::GetSelectMenuText( EDA_UNITS aUnits ) const
{
    return wxString::Format( _( "Graphic Text \"%s\"" ), ShortenedShownText() );
}


BITMAP_DEF LIB_TEXT::GetMenuImage() const
{
    return text_xpm;
}


void LIB_TEXT::BeginEdit( const wxPoint aPosition )
{
    SetTextPos( aPosition );
}


void LIB_TEXT::CalcEdit( const wxPoint& aPosition )
{
    SetTextPos( aPosition );
}
