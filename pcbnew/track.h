/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004 Jean-Pierre Charras, jaen-pierre.charras@gipsa-lab.inpg.com
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

/**
 * @file class_track.h
 * @brief A single base class (TRACK) represents both tracks and vias, with subclasses
 * for curved tracks (ARC) and vias (VIA).  All told there are three KICAD_Ts:
 * PCB_TRACK_T, PCB_ARC_T, and PCB_VIA_T.
 *
 * For vias there is a further VIATYPE which indicates THROUGH, BLIND_BURIED, or
 * MICROVIA, which are supported by the synthetic KICAD_Ts PCB_LOCATE_STDVIA_T,
 * PCB_LOCATE_BBVIA_T, and PCB_LOCATE_UVIA_T.
 */

#ifndef CLASS_TRACK_H
#define CLASS_TRACK_H


#include <board_connected_item.h>
#include <convert_to_biu.h>


class TRACK;
class VIA;
class PAD;
class MSG_PANEL_ITEM;
class SHAPE_POLY_SET;
class SHAPE_ARC;


// Flag used in locate routines (from which endpoint work)
enum ENDPOINT_T : int
{
    ENDPOINT_START = 0,
    ENDPOINT_END = 1
};

// Via types
// Note that this enum must be synchronized to GAL_LAYER_ID
enum class VIATYPE : int
{
    THROUGH      = 3, /* Always a through hole via */
    BLIND_BURIED = 2, /* this via can be on internal layers */
    MICROVIA     = 1, /* this via which connect from an external layer
                                * to the near neighbor internal layer */
    NOT_DEFINED  = 0  /* not yet used */
};

#define UNDEFINED_DRILL_DIAMETER  -1       //< Undefined via drill diameter.

// Used for tracks and vias for algorithmic safety, not to enforce constraints
#define GEOMETRY_MIN_SIZE ( int )( 0.001 * IU_PER_MM )


class TRACK : public BOARD_CONNECTED_ITEM
{
public:
    static inline bool ClassOf( const EDA_ITEM* aItem )
    {
        return aItem && PCB_TRACE_T == aItem->Type();
    }

    TRACK( BOARD_ITEM* aParent, KICAD_T idtype = PCB_TRACE_T );

    // Do not create a copy constructor.  The one generated by the compiler is adequate.

    void Move( const wxPoint& aMoveVector ) override
    {
        m_Start += aMoveVector;
        m_End   += aMoveVector;
    }

    void Rotate( const wxPoint& aRotCentre, double aAngle ) override;

    void Flip( const wxPoint& aCentre, bool aFlipLeftRight ) override;

    void SetPosition( const wxPoint& aPos ) override { m_Start = aPos; }
    wxPoint GetPosition() const override { return m_Start; }
    const wxPoint GetFocusPosition() const override { return ( m_Start + m_End ) / 2; }

    void SetWidth( int aWidth )                 { m_Width = aWidth; }
    int GetWidth() const                        { return m_Width; }

    void SetEnd( const wxPoint& aEnd )          { m_End = aEnd; }
    const wxPoint& GetEnd() const               { return m_End; }

    void SetStart( const wxPoint& aStart )      { m_Start = aStart; }
    const wxPoint& GetStart() const             { return m_Start; }

    void SetEndX( int aX ) { m_End.x = aX; }
    void SetEndY( int aY ) { m_End.y = aY; }

    int GetEndX() const { return m_End.x; }
    int GetEndY() const { return m_End.y; }

    /// Return the selected endpoint (start or end)
    const wxPoint& GetEndPoint( ENDPOINT_T aEndPoint ) const
    {
        if( aEndPoint == ENDPOINT_START )
            return m_Start;
        else
            return m_End;
    }

    // Virtual function
    const EDA_RECT GetBoundingBox() const override;

    /**
     * Function GetLength
     * returns the length of the track using the hypotenuse calculation.
     * @return double - the length of the track
     */
    virtual double GetLength() const;

    /**
     * Function TransformShapeWithClearanceToPolygon
     * Convert the track shape to a closed polygon
     * Used in filling zones calculations
     * Circles (vias) and arcs (ends of tracks) are approximated by segments
     * @param aCornerBuffer = a buffer to store the polygon
     * @param aClearanceValue = the clearance around the pad
     * @param aError = the maximum deviation from true circle
     * @param ignoreLineWidth = used for edge cut items where the line width is only
     * for visualization
     */
    void TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer,
                                               PCB_LAYER_ID aLayer, int aClearanceValue,
                                               int aError, ERROR_LOC aErrorLoc,
                                               bool ignoreLineWidth = false ) const override;

    // @copydoc BOARD_ITEM::GetEffectiveShape
    virtual std::shared_ptr<SHAPE> GetEffectiveShape( PCB_LAYER_ID aLayer = UNDEFINED_LAYER ) const override;

    /**
     * Function IsPointOnEnds
     * returns STARTPOINT if point if near (dist = min_dist) start point, ENDPOINT if
     * point if near (dist = min_dist) end point,STARTPOINT|ENDPOINT if point if near
     * (dist = min_dist) both ends, or 0 if none of the above.
     * if min_dist < 0: min_dist = track_width/2
     */
    STATUS_FLAGS IsPointOnEnds( const wxPoint& point, int min_dist = 0 ) const;

    /**
     * Function IsNull
     * returns true if segment length is zero.
     */
    bool IsNull() const
    {
        return ( Type() == PCB_VIA_T ) || ( m_Start == m_End );
    }

    void GetMsgPanelInfo( EDA_DRAW_FRAME* aFrame, std::vector<MSG_PANEL_ITEM>& aList ) override;

    SEARCH_RESULT Visit( INSPECTOR inspector, void* testData, const KICAD_T scanTypes[] ) override;

    bool HitTest( const wxPoint& aPosition, int aAccuracy = 0 ) const override;
    bool HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy = 0 ) const override;

    bool ApproxCollinear( const TRACK& aTrack );

    wxString GetClass() const override
    {
        return wxT( "TRACK" );
    }

    /**
     * Function GetLocalClearance
     * returns any local clearance overrides set in the "classic" (ie: pre-rule) system.
     * @param aSource [out] optionally reports the source as a user-readable string
     * @return int - the clearance in internal units.
     */
    int GetLocalClearance( wxString* aSource ) const override;

    void GetWidthConstraints( int* aMin, int* aMax, wxString* aSource ) const;

    wxString GetSelectMenuText( EDA_UNITS aUnits ) const override;

    BITMAPS GetMenuImage() const override;

    virtual EDA_ITEM* Clone() const override;

    virtual void ViewGetLayers( int aLayers[], int& aCount ) const override;

    double ViewGetLOD( int aLayer, KIGFX::VIEW* aView ) const override;

    const BOX2I ViewBBox() const override;

    virtual void SwapData( BOARD_ITEM* aImage ) override;

    /**
     * @return true because a track or a via is always on a copper layer.
     */
    bool IsOnCopperLayer() const override
    {
        return true;
    }

    struct cmp_tracks
    {
        bool operator()( const TRACK* aFirst, const TRACK* aSecond ) const;
    };

#if defined (DEBUG)
    virtual void Show( int nestLevel, std::ostream& os ) const override { ShowDummy( os ); }

    /**
     * Function ShowState
     * converts a set of state bits to a wxString
     * @param stateBits Is an OR-ed together set of bits like IN_EDIT, etc.
     */
    static wxString ShowState( int stateBits );

#endif

protected:
    void GetMsgPanelInfoBase_Common( EDA_DRAW_FRAME* aFrame, std::vector<MSG_PANEL_ITEM>& aList ) const;


    int         m_Width;            ///< Thickness of track, or via diameter
    wxPoint     m_Start;            ///< Line start point
    wxPoint     m_End;              ///< Line end point

};


class ARC : public TRACK
{
public:
    ARC( BOARD_ITEM* aParent ) : TRACK( aParent, PCB_ARC_T ){};

    ARC( BOARD_ITEM* aParent, const SHAPE_ARC* aArc );

    static inline bool ClassOf( const EDA_ITEM *aItem )
    {
        return aItem && PCB_ARC_T == aItem->Type();
    }

    virtual void Move( const wxPoint& aMoveVector ) override
    {
        m_Start += aMoveVector;
        m_Mid   += aMoveVector;
        m_End   += aMoveVector;
    }

    virtual void Rotate( const wxPoint& aRotCentre, double aAngle ) override;

    virtual void Flip( const wxPoint& aCentre, bool aFlipLeftRight ) override;

    void SetMid( const wxPoint& aMid )          { m_Mid = aMid; }
    const wxPoint& GetMid() const               { return m_Mid; }

    void SetPosition( const wxPoint& aPos ) override
    {
        m_Start = aPos;
    }

    virtual wxPoint GetPosition() const override;

    virtual wxPoint GetCenter() const override { return GetPosition(); }

    double GetRadius() const;
    double GetAngle() const;
    double GetArcAngleStart() const;
    double GetArcAngleEnd() const;
    virtual bool HitTest( const wxPoint& aPosition, int aAccuracy = 0 ) const override;

    virtual bool HitTest( const EDA_RECT& aRect, bool aContained = true, int aAccuracy = 0 ) const override;

    wxString GetClass() const override
    {
        return wxT( "ARC" );
    }

    // @copydoc BOARD_ITEM::GetEffectiveShape
    virtual std::shared_ptr<SHAPE> GetEffectiveShape( PCB_LAYER_ID aLayer = UNDEFINED_LAYER ) const override;

    //TODO(snh): Add GetSelectMenuText() and GetMsgPanelInfoBase()

    /**
     * Function GetLength
     * returns the length of the arc track
     * @return double - the length of the track
     */
    virtual double GetLength() const override
    {
        double radius = GetRadius();
        double includedAngle  = std::abs( GetAngle() );

        return radius * M_PI * includedAngle / 1800.0;
    }

    EDA_ITEM* Clone() const override;

    virtual void SwapData( BOARD_ITEM* aImage ) override;

private:
    wxPoint     m_Mid;                      ///< Arc mid point, halfway between start and end
};


class VIA : public TRACK
{
public:
    VIA( BOARD_ITEM* aParent );

    static inline bool ClassOf( const EDA_ITEM *aItem )
    {
        return aItem && PCB_VIA_T == aItem->Type();
    }

    // Do not create a copy constructor.  The one generated by the compiler is adequate.

    bool IsType( const KICAD_T aScanTypes[] ) const override
    {
        if( BOARD_CONNECTED_ITEM::IsType( aScanTypes ) )
            return true;

        for( const KICAD_T* p = aScanTypes; *p != EOT; ++p )
        {
            if( *p == PCB_LOCATE_STDVIA_T && m_viaType == VIATYPE::THROUGH )
                return true;
            else if( *p == PCB_LOCATE_UVIA_T && m_viaType == VIATYPE::MICROVIA )
                return true;
            else if( *p == PCB_LOCATE_BBVIA_T && m_viaType == VIATYPE::BLIND_BURIED )
                return true;
        }

        return false;
    }

    VIATYPE GetViaType() const { return m_viaType; }
    void SetViaType( VIATYPE aViaType ) { m_viaType = aViaType; }

    bool IsOnLayer( PCB_LAYER_ID aLayer ) const override;

    virtual LSET GetLayerSet() const override;
    virtual void SetLayerSet( LSET aLayers ) override;

    /**
     * Function SetLayerPair
     * For a via m_layer contains the top layer, the other layer is in m_bottomLayer
     * @param aTopLayer = first layer connected by the via
     * @param aBottomLayer = last layer connected by the via
     */
    void SetLayerPair( PCB_LAYER_ID aTopLayer, PCB_LAYER_ID aBottomLayer );

    void SetBottomLayer( PCB_LAYER_ID aLayer );
    void SetTopLayer( PCB_LAYER_ID aLayer );

    /**
     * Function LayerPair
     * Return the 2 layers used by  the via (the via actually uses
     * all layers between these 2 layers)
     *  @param top_layer = pointer to the first layer (can be null)
     *  @param bottom_layer = pointer to the last layer (can be null)
     */
    void LayerPair( PCB_LAYER_ID* top_layer, PCB_LAYER_ID* bottom_layer ) const;

    PCB_LAYER_ID TopLayer() const;
    PCB_LAYER_ID BottomLayer() const;

    /**
     * Function SanitizeLayers
     * Check so that the layers are correct dependin on the type of via, and
     * so that the top actually is on top.
     */
    void SanitizeLayers();

    wxPoint GetPosition() const override {  return m_Start; }
    void SetPosition( const wxPoint& aPoint ) override { m_Start = aPoint;  m_End = aPoint; }

    void GetMsgPanelInfo( EDA_DRAW_FRAME* aFrame, std::vector<MSG_PANEL_ITEM>& aList ) override;

    bool HitTest( const wxPoint& aPosition, int aAccuracy = 0 ) const override;
    bool HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy = 0 ) const override;

    wxString GetClass() const override
    {
        return wxT( "VIA" );
    }

    wxString GetSelectMenuText( EDA_UNITS aUnits ) const override;

    BITMAPS GetMenuImage() const override;

    EDA_ITEM* Clone() const override;

    void ViewGetLayers( int aLayers[], int& aCount ) const override;

    double ViewGetLOD( int aLayer, KIGFX::VIEW* aView ) const override;

    void Flip( const wxPoint& aCentre, bool aFlipLeftRight ) override;

#if defined (DEBUG)
    void Show( int nestLevel, std::ostream& os ) const override { ShowDummy( os ); }
#endif

    int GetMinAnnulus( PCB_LAYER_ID aLayer, wxString* aSource ) const;

    /**
     * Sets the unconnected removal property.  If true, the copper is removed on zone fill
     * or when specifically requested when the via is not connected on a layer.
     */
    void SetRemoveUnconnected( bool aSet )      { m_removeUnconnectedLayer = aSet; }
    bool GetRemoveUnconnected() const           { return m_removeUnconnectedLayer; }

    /**
     * Sets whether we keep the top and bottom connections even if they are not connected
     */
    void SetKeepTopBottom( bool aSet )      { m_keepTopBottomLayer = aSet; }
    bool GetKeepTopBottom() const           { return m_keepTopBottomLayer; }

    /**
     * Checks to see whether the via should have a pad on the specific layer
     * @param aLayer Layer to check for connectivity
     * @return true if connected by pad or track (or optionally zone)
     */
    bool FlashLayer( int aLayer ) const;

    /**
     * Checks to see if the via is present on any of the layers in the set
     * @param aLayers set of layers to check the via against
     * @return true if connected by pad or track (or optionally zone) on any of the associated layers
     */
    bool FlashLayer( LSET aLayers ) const;

    /**
     * Function SetDrill
     * sets the drill value for vias.
     * @param aDrill is the new drill diameter
    */
    void SetDrill( int aDrill )             { m_drill = aDrill; }

    /**
     * Function GetDrill
     * returns the local drill setting for this VIA.  If you want the calculated value,
     * use GetDrillValue() instead.
     */
    int GetDrill() const                    { return m_drill; }

    /**
     * Function GetDrillValue
     * "calculates" the drill value for vias (m-Drill if > 0, or default
     * drill value for the board.
     * @return real drill_value
    */
    int GetDrillValue() const;

    /**
     * Function SetDrillDefault
     * sets the drill value for vias to the default value #UNDEFINED_DRILL_DIAMETER.
    */
    void SetDrillDefault()      { m_drill = UNDEFINED_DRILL_DIAMETER; }

    /**
     * Checks if the via is a free via (as opposed to one created on a track by the router).
     * Free vias don't have their nets automatically updated by the connectivity algorithm.
     * @return true if the via is a free via
     */
    bool GetIsFree() const { return m_isFree; }
    void SetIsFree( bool aFree = true ) { m_isFree = aFree; }

    /**
     * Function IsDrillDefault
     * @return true if the drill value is default value (-1)
    */
    bool IsDrillDefault() const { return m_drill <= 0; }

    void SwapData( BOARD_ITEM* aImage ) override;

    // @copydoc BOARD_ITEM::GetEffectiveShape
    std::shared_ptr<SHAPE> GetEffectiveShape( PCB_LAYER_ID aLayer = UNDEFINED_LAYER ) const override;

protected:
    wxString layerMaskDescribe() const override;

private:
    /// The bottom layer of the via (the top layer is in m_layer)
    PCB_LAYER_ID m_bottomLayer;

    VIATYPE      m_viaType;                  ///< through, blind/buried or micro

    int          m_drill;                    ///< for vias: via drill (- 1 for default value)

    bool         m_removeUnconnectedLayer;   ///< Remove unconnected copper on a via
    bool         m_keepTopBottomLayer;       ///< Keep the top and bottom annular rings
    bool         m_isFree;                   ///< "Free" vias don't get their nets auto-updated
};


#endif // CLASS_TRACK_H
