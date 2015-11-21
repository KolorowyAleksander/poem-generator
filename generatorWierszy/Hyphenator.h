/* libhyphenate: A TeX-like hyphenation algorithm.
 * Copyright (C) 2007 Steve Wolter
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * If you have any questions, feel free to contact me:
 * http://swolter.sdf1.org
 **/
#ifndef HYPHENATE_HYPHENATOR_H
#define HYPHENATE_HYPHENATOR_H

#include "Language.h"
#include <map>
#include <string>
#include <memory>

namespace Hyphenate {
   class HyphenationTree;

   class Hyphenator {
      private:
	 std::auto_ptr<HyphenationTree> dictionary;

      public:
         /** Build a hyphenator for the given language. The hyphenation
          *  patterns for the language will loaded from a file named like
          *  the language string or any prefix of it. The file will be
          *  located in the directory given by the environment variable
          *  LIBHYPHENATE_PATH or, if this is empty, in the compiled-in
          *  pattern directory which defaults to 
          *  /usr/local/share/libhyphenate/patterns .
          *
          * \param lang The language for which hyphenation patterns will be
          *             loaded. */
	 Hyphenator(const RFC_3066::Language& lang); 

         /** Destructor. */
	 ~Hyphenator();

         /** The actual workhorse. You'll want to call this function once
         * for each word you want hyphenated.  
         *  
         *  Usage example: 
         *  	Hyphenate::Hyphenator hyphenator(Language("de-DE"));
         *  	hyphenator.hyphenate("Schifffahrt");
         *
         *  	yields "Schiff-fahrt", while 
         *
         *  	Hyphenate::Hyphenator hyphenator(Language("en"));
         *  	hyphenator.hyphenate("example", "&shy;");
         *
         *  	yields "ex&shy;am&shy;ple".
         *
         *  \param word A single UTF-8 encoded word to be hyphenated.
         *  \param hyphen The string to put at each possible
         *                hyphenation point. The default is an ASCII dash.
         */
	 std::string hyphenate
		  (const std::string &word,
		   const std::string &hyphen = "-")
		  throw(std::domain_error);
   };
}

#endif
