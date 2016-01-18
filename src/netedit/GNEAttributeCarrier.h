/****************************************************************************/
/// @file    GNEAttributeCarrier.h
/// @author  Jakob Erdmann
/// @date    Mar 2011
/// @version $Id$
///
// Abstract Base class for gui objects which carry attributes
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2015 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNEAttributeCarrier_h
#define GNEAttributeCarrier_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <vector>
#include <map>
#include <utils/xml/SUMOXMLDefinitions.h>
#include <utils/common/ToString.h>
#include "GNEReferenceCounter.h"


// ===========================================================================
// class declarations
// ===========================================================================
class GNENet;
class GNEUndoList;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNEAttributeCarrier
 *
 * Abstract Base class for gui objects which carry attributes
 * inherits from GNEReferenceCounter for convenience
 */
class GNEAttributeCarrier : public GNEReferenceCounter {
    /// @brief declare friend class
    friend class GNEChange_Attribute;

public:

    /** @brief Constructor
     * @param[in] tag SUMO Tag assigned to this type of object
     */
    GNEAttributeCarrier(SumoXMLTag tag);

    /// @brief Destructor
    virtual ~GNEAttributeCarrier() {};

    /* @brief method for getting the Attribute of an XML key
     * @param[in] key The attribute key
     * @return string with the value associated to key
     */
    virtual std::string getAttribute(SumoXMLAttr key) const = 0;

    /* @brief method for setting the attribute and letting the object perform additional changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     * @param[in] net optionally the GNENet to inform about gui updates
     */
    virtual void setAttribute(SumoXMLAttr key, const std::string& value, GNEUndoList* undoList) = 0;

    /* @brief method for checking if the key and their conrrespond attribute are valids
     * @param[in] key The attribute key
     * @param[in] value The value asociated to key key
     * @return true if the value is valid, false in other case
     */
    virtual bool isValid(SumoXMLAttr key, const std::string& value);

    /// @brief how should this attribute carrier be called
    virtual std::string getDescription();

    /// @brief get Tag assigned to this object
    SumoXMLTag getTag() const;

    /// @brief get vector of attributes
    const std::vector<SumoXMLAttr>& getAttrs() const;

    /// @brief function to support debugging
    const std::string getID() const;

    /// @brief get all editable attributes for tag.
    static const std::vector<SumoXMLAttr>& allowedAttributes(SumoXMLTag tag);

    /// @brief get all editable attributes for tag.
    static const std::vector<SumoXMLTag>& allowedTags();

    /// @brief whether an attribute is numerical
    static bool isNumerical(SumoXMLAttr attr);

    /// @brief whether an attribute is unique (may not be edited for a multi-selection)
    static bool isUnique(SumoXMLAttr attr);

    /// @brief return a list of discrete choices for this attribute or an empty vector
    static const std::vector<std::string>& discreteChoices(SumoXMLTag tag, SumoXMLAttr attr);

    /// @brief return whether the given attribute allows for a combination of discrete values
    static bool discreteCombinableChoices(SumoXMLTag tag, SumoXMLAttr attr);

    /// @brief true if an object of type T can be parsed from string
    template <class T>
    static bool canParse(const std::string& string) {
        T tmp;
        std::istringstream buf(string);
        buf >> tmp;
        return !buf.fail() && (size_t)buf.tellg() == string.size();
    }

    /// @brief parses an object of type T from from string
    template <class T>
    static T parse(const std::string& string) {
        T result;
        std::istringstream buf(string);
        buf >> result;
        return result;
    }

    /// @brief true if a positive number of type T can be parsed from string
    template <class T>
    static bool isPositive(const std::string& string) {
        if (canParse<T>(string)) {
            return parse<T>(string) > 0;
        } else {
            return false;
        }
    }

    /// @brief true if value is a valid sumo ID
    static bool isValidID(const std::string& value);

    /// @brief feature is still unchanged after being loaded (implies approval)
    static const std::string LOADED;

    /// @brief feature has been reguessed (may still be unchanged be we can't tell (yet)
    static const std::string GUESSED;

    /// @brief feature has been manually modified (implies approval)
    static const std::string MODIFIED;

    /// @brief feature has been approved but not changed (i.e. after being reguessed)
    static const std::string APPROVED;


private:
    /// @brief method for setting the attribute and nothing else (used in GNEChange_Attribute)
    virtual void setAttribute(SumoXMLAttr key, const std::string& value) = 0;

    /// @brief the xml tag to which this carrier corresponds
    const SumoXMLTag myTag;

    /// @brief map with the allowed attributes
    static std::map<SumoXMLTag, std::vector<SumoXMLAttr> > _allowedAttributes;

    /// @brief map with the allowed tags
    static std::vector<SumoXMLTag> _allowedTags;

    /// @brief map with the numerical attributes
    static std::set<SumoXMLAttr> _numericalAttrs;

    /// @brief map with the unique attributes
    static std::set<SumoXMLAttr> _uniqueAttrs;

    /// @brief map with the values of discrete choices
    static std::map<SumoXMLTag, std::map<SumoXMLAttr, std::vector<std::string> > > _discreteChoices;

private:
    /// @brief Invalidated assignment operator
    GNEAttributeCarrier& operator=(const GNEAttributeCarrier& src);
};

#endif

/****************************************************************************/

