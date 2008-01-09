/*
**********************************************************************
* Copyright (c) 2004-2008, International Business Machines
* Corporation and others.  All Rights Reserved.
**********************************************************************
* Author: Alan Liu
* Created: April 20, 2004
* Since: ICU 3.0
**********************************************************************
*/
#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING

#include "currfmt.h"
#include "unicode/numfmt.h"

U_NAMESPACE_BEGIN

CurrencyFormat::CurrencyFormat(const Locale& locale, UErrorCode& ec) :
    fmt(NULL) {
    fmt = NumberFormat::createCurrencyInstance(locale, ec);
}

CurrencyFormat::CurrencyFormat(const CurrencyFormat& other) :
    MeasureFormat(other), fmt(NULL) {
    fmt = (NumberFormat*) other.fmt->clone();
}

CurrencyFormat::~CurrencyFormat() {
	if (fmt != NULL) {
		delete fmt;
	}
}

UBool CurrencyFormat::operator==(const Format& other) const {
    if (this == &other) {
        return TRUE;
    }
    if (other.getDynamicClassID() != CurrencyFormat::getStaticClassID()) {
        return FALSE;
    }
    const CurrencyFormat* c = (const CurrencyFormat*) &other;
    return *fmt == *c->fmt;
}

Format* CurrencyFormat::clone() const {
    return new CurrencyFormat(*this);
}

UnicodeString& CurrencyFormat::format(const Formattable& obj,
                                      UnicodeString& appendTo,
                                      FieldPosition& pos,
                                      UErrorCode& ec) const {
	if (fmt != NULL) {
		return fmt->format(obj, appendTo, pos, ec);
	} 
	// Set error code; fmt should never be NULL
	// this is the case due to failure in construction process
	ec = U_MEMORY_ALLOCATION_ERROR;
	return appendTo;
}

void CurrencyFormat::parseObject(const UnicodeString& source,
                                 Formattable& result,
                                 ParsePosition& pos) const {
	if (fmt != NULL) {
		fmt->parseCurrency(source, result, pos);
	}
}

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(CurrencyFormat)

U_NAMESPACE_END

#endif /* #if !UCONFIG_NO_FORMATTING */
