/****************************************************************************/
/// @file    GNEInspector.h
/// @author  Jakob Erdmann
/// @date    Mar 2011
/// @version $Id$
///
// The Widget for modifying network-element attributes (i.e. lane speed)
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2016 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNEInspector_h
#define GNEInspector_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <utils/xml/SUMOXMLDefinitions.h>
#include "GNEDynamicFrame.h"

// ===========================================================================
// class declarations
// ===========================================================================
class GNENet;
class GNEEdge;
class GNEAttributeCarrier;
class GNEUndoList;
class GNEAdditional;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNEInspector
 * The Widget for modifying network-element attributes (i.e. lane speed)
 */
class GNEInspector : public FXScrollWindow {
    // FOX-declarations
    FXDECLARE(GNEInspector)

public:
    // ===========================================================================
    // class AttrPanel
    // ===========================================================================
    class AttrPanel : public FXVerticalFrame {
        // FOX-declarations
        FXDECLARE(GNEInspector::AttrPanel)

    public:
        /// @brief constructor
        AttrPanel(GNEInspector* parent, const std::vector<GNEAttributeCarrier*>& ACs, GNEUndoList* undoList);

        /// @brief try to set new attribute value
        long onCmdSetBlocking(FXObject*, FXSelector, void*);

    protected:
        /// @brief FOX needs this
        AttrPanel() {}

    private:
        /// @brief pointer to check button block
        FXCheckButton *myCheckBlocked;

        /// @brief pointer to additional element
        GNEAdditional *myAdditional;
    };

    // ===========================================================================
    // class AttrInput
    // ===========================================================================
    class AttrInput : public FXHorizontalFrame {
        // FOX-declarations
        FXDECLARE(GNEInspector::AttrInput)

    public:
        /// @brief constructor
        AttrInput(FXComposite* parent, const std::vector<GNEAttributeCarrier*>& ACs, SumoXMLAttr attr,
                  std::string initialValue, GNEUndoList* undoList);

        /// @brief try to set new attribute value
        long onCmdSetAttribute(FXObject*, FXSelector, void*);

        /// @brief open model dialog for more comfortable attribute editing
        long onCmdOpenAttributeEditor(FXObject*, FXSelector, void*);

    protected:
        /// @brief FOX needs this
        AttrInput() {}

    private:
        /// @brief actual tag
        SumoXMLTag myTag;

        /// @brief attributos
        SumoXMLAttr myAttr;

        /// @brief attribute carriers
        const std::vector<GNEAttributeCarrier*>* myACs;

        /// @brief pointer to undolist
        GNEUndoList* myUndoList;

        /// @brief pointer to text field
        FXTextField* myTextField;

        /// @brief pointer to combo box choices
        FXComboBox* myChoicesCombo;
    };

public:
    /** @brief Constructor
     * @param[in] parent The parent window
     * @param[in] undoList The undoList to record changes facilitated by this
     * @param[in] tpl The initial edge template (we assume shared responsibility via reference counting)
     */
    GNEInspector(FXComposite* parent, GNEUndoList* undoList);

    /// @brief Destructor
    ~GNEInspector();

    /// @brief Inspect the given multi-selection
    void inspect(const std::vector<GNEAttributeCarrier*>& ACs);

    /// @brief Creates the widget
    void create();

    /// @brief update the widget
    void update();

    /// @brief get Header Font
    FXFont* getHeaderFont() const;

    /// @brief get the template edge (to copy attributes from)
    GNEEdge* getEdgeTemplate() const;

    /// @brief seh the template edge (we assume shared responsibility via reference counting)
    void setEdgeTemplate(GNEEdge* tpl);

    /// @brief copy edge attributes from edge template
    long onCmdCopyTemplate(FXObject*, FXSelector, void*);

    /// @brief set current edge as new template
    long onCmdSetTemplate(FXObject*, FXSelector, void*);

    /// @brief update the copy button with the name of the template
    long onUpdCopyTemplate(FXObject*, FXSelector, void*);

protected:
    /// @brief FOX needs this
    GNEInspector() {}

private:
    /// @brief pointer to undo list
    GNEUndoList* myUndoList;

    /// @brief Font for the widget
    FXFont* myHeaderFont;

    /// @brief panel of attributes
    AttrPanel* myPanel;

    /// @brief the edge template
    GNEEdge* myEdgeTemplate;

    /// @brief the multi-selection currently being inspected
    std::vector<GNEAttributeCarrier*> myACs;

    /// @brief Width of the frame
    static const int WIDTH;
};


#endif

/****************************************************************************/

