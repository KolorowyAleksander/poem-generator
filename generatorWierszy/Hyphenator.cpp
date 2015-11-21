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
#include "Hyphenator.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
using namespace RFC_3066;
using namespace Hyphenate;

/* The HyphenationNode is a tree node for the hyphenation search tree. It
 * represents the matching state after a single character; if there is a
 * pattern that ends with that particular character, the hyphenation_pattern
 * is set to non-NULL. The jump_table links to the children of that node,
 * indexed by letters. */
class HyphenationNode {
   public:
      /* Table of children */
      map<char, HyphenationNode*> jump_table;
      /* Hyphenation pattern associated with the full path to this node. */
      auto_ptr<vector<char> > hyphenation_pattern;

      HyphenationNode() {}
      ~HyphenationNode() {
	 /* The destructor has to destroy all childrens. */
	 for (map<char, HyphenationNode*>::iterator i = jump_table.begin();
	       i != jump_table.end(); i++)
	    delete i->second;
      }

      /** Find a particular jump table entry, or NULL if there is none for that
        * letter. */
      inline const HyphenationNode *find(char arg) const {
	 map<char, HyphenationNode*>::const_iterator i =
	    jump_table.find(arg);
	 if (i != jump_table.end()) return i->second; else return NULL;
      }
      /** Find a particular jump table entry, or NULL if there is none for that
        * letter. */
      inline HyphenationNode *find(char arg) {
	 map<char, HyphenationNode*>::iterator i = jump_table.find(arg);
	 if (i != jump_table.end()) return i->second; else return NULL;
      }

      /** Insert a particular hyphenation pattern into the hyphenation tree.
        * \param pattern The character pattern to match in the input word.
	* \param hp The digit-pattern for the hyphenation algorithm.
	*/
      void insert (const char *pattern, const vector<char> &hp);
};

/**
 * \class HyphenationTree
 * \brief The root for a tree of HyphenationNodes
 */
class Hyphenate::HyphenationTree {
   public:
      auto_ptr<HyphenationNode> root;
      int start_safe, end_safe;

      HyphenationTree() : root(new HyphenationNode()) {}
};

void HyphenationNode::insert (const char *pattern, const vector<char>& hp) {
   /* Is this the terminal node for that pattern? */
   if (! *pattern) {
      /* If we descended the tree all the way to the last letter, we can now
       * write the pattern into this node. */
      hyphenation_pattern.reset(new vector<char>(hp));
   } else {
      /* Check for an already present branch for that letter. */
      HyphenationNode *p = find(*pattern);
      if (!p) {
	 /* If there is none, create one. */
	 p = new HyphenationNode();
	 jump_table.insert(pair<char, HyphenationNode*>(*pattern, p));
      }
      /* Go to the next letter and descend. */
      p->insert(pattern+1, hp);
   }
}

/** This method applies all possible hyphenation patterns from the supplied
 *  HyphenationNode tree and writes the results in the supplied buffer.
 *
 *  \param n HyphenationTree containing the pattern rules.
 *  \param hyph_buffer A character vector with a length of at least
 *                     strlen(to_match)+1 that can take the hyphenation
 *                     hints (the 0-9 digits).
 *  \param to_match    The string to find hyphenation patterns for. Watch
 *                     out: only prefixes of that string will be matched
 *                     against the patterns. You'll have to call this method
 *                     once for each possible prefix of the string. */
static void apply_patterns(const HyphenationNode *n, char *hyph_buffer, 
   const char *to_match) 
{
   /* First of all, if we can descend further into the tree (that is,
    * there is an input char left and there is a branch in the tree),
    * do so. */
   if (*to_match)
      if (const HyphenationNode *next = n->find(*to_match))
	 apply_patterns(next, hyph_buffer, to_match+1);

   /* Now, if we have a pattern at this point in the tree, it must be a good
    * match. */
   if (const vector<char>* hyp_pat = n->hyphenation_pattern.get())
      for (int i = 0; i < hyp_pat->size(); i++)
	 hyph_buffer[i] = max<char>((*hyp_pat)[i], hyph_buffer[i]);
}

/** The hyphenation table parser. */
static auto_ptr<HyphenationTree> read_hyphenation_table(const char *filename) {
   ifstream i (filename, fstream::in);
   string pattern;
   vector<char> hyphs;
   auto_ptr<HyphenationTree> output(new HyphenationTree());

   const int HAD_NUMBER = 0;
   const int NO_NUMBER = 1;
   int state = NO_NUMBER;		/* Simple state machine. */

   /* First of all, the first line contains two numbers we are
    * searching for - the number of characters at the start and the
    * end of the word that won't be hyphenated off. */
   i >> output->start_safe >> output->end_safe;
   /* The rest of the input is a file with whitespace-separated words, which
    * are letters and dots prefixed by a digit each. The digit may
    * be omitted, in which case it defaults to 0. */
   char ch;
   while ( i.get(ch) ) {
      if (isdigit(ch) && state == HAD_NUMBER) {
	 /* Multiple digits form a number. No idea if this is actually
	  * needed, but I figured that if 1...8 are used (for german, for example),
	  * 10 might be needed as well. Better don't choke up on it :-) */
	 hyphs.back() *= 10;
	 hyphs.back() += ch - '0';
      } else if (isdigit(ch) && state == NO_NUMBER) {
	 /* OK, we get only single digits here. Whenever we find one,
	  * it is a digit replacing the default 0; append it to the hyphenation
	  * vector and remember we found a digit. */
	 hyphs.push_back(ch - '0');
	 state = HAD_NUMBER;
      } else if (isspace(ch)) {
	 /* A space means next pattern. Write our after-word-digit first. */
	 if (state == NO_NUMBER)
	    hyphs.push_back(0);

	 /* The output operation. */
	 if (pattern.size())
	    output->root->insert(pattern.c_str(), hyphs);

	 /* Reinitialize state. */
	 state = NO_NUMBER;
	 hyphs.clear();
	 pattern.clear();
      } else {
	 /* This rule catches all other (mostly alpha, but probably UTF-8)
	  * characters. It just appends to the pattern, appending the default
	  * 0 to the hyphenation vector if necessary. */
	 if (state == NO_NUMBER)
	    hyphs.push_back(0);
	 state = NO_NUMBER;

	 pattern += ch;
      }
   }

   return output;
}

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
Hyphenate::Hyphenator::Hyphenator(const RFC_3066::Language& lang) {
   string path = "";

/*   if (getenv("LIBHYPHENATE_PATH")) {
      path = getenv("LIBHYPHENATE_PATH");
   }

#ifdef LIBHYPHENATE_DEFAULT_PATH
   if (path == "")
      path = LIBHYPHENATE_DEFAULT_PATH;
#endif*/

   path = "generatorWierszy/en";

   string filename = "en";
   dictionary = read_hyphenation_table(filename.c_str());
}

/** The actual workhorse. You'll want to call this function once for each word
 *  you want hyphenated.  
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
 *  \param word A single word to be hyphenated.
 *  \param hyphen The string to put at each possible hyphenation location. The
 *  		  default is a stupid ASCII dash.
 */
string Hyphenate::Hyphenator::hyphenate(const string& word, 
   const string &hyphen) throw(std::domain_error)
{
   HyphenationTree &dict = *dictionary;

   /* The '.' is the word-boundary marker. Several patterns apply only at a
    * word boundary. */
   string w = '.' + word + '.';
   vector<char> pattern(w.size()+1,0);
   vector<int> character(w.size());

   /* First of all, label the UTF-8 characters in the word with numbers. */
   character[0] = -1;
   for (int i = 1; i < w.size(); i++)
      if (w[i] >= 0 || (w[i] & 0xC0) == 0xC0)
         character[i] = character[i-1]+1;
      else
         character[i] = character[i-1];

   /* Remember the . at the end. */
   int last_character = character[w.size()-2];

   /* Now, for each suffix of the expanded word, search all matching prefixes.
    * That way, each possible match is found. Note the pointer arithmethics
    * in the second and third argument. */
   for (int i = 0; i < w.size()-1; i++)
      apply_patterns(dict.root.get(), (&pattern[0]) + i, w.c_str() + i);

   /* Build our result string. Of course, we _could_ insert characters in
    * w, but that would be highly inefficient. */
   string result;

   for (int i = 1; i < w.size()-1; i++) {
      /* We honor the safe areas at the start and end of each word here.
       * Please note that the incongruence between start and end is due
       * to the fact that hyphenation happens _before_ each character. */
      if ( character[i] != character[i-1] &&
           pattern[i] % 2 == 1 &&
           character[i] >= dict.start_safe && 
           character[i] <= last_character+1-dict.end_safe)
	 result += hyphen;

      result += w[i];
   }
   return result;
}

Hyphenator::~Hyphenator() {}
