#include <assert.h>
#include <sstream>

#include "CMove.h"

bool CMove::WK_moved= false;
bool CMove::WRL_moved= false;
bool CMove::WRR_moved= false;
bool CMove::BK_moved= false;
bool CMove::BRL_moved= false;
bool CMove::BRR_moved= false;

bool CMove::en_passant_ready= false;
bool CMove::en_passant_played= false;
int CMove::en_passant_square= -1;

std::ostream&
operator<<(std::ostream& os, const CMove& rhs)
{
    return os << rhs.ToShortString();
} // end of std::ostream& operator <<(std::ostream &os, const CMove &rhs)

static char pieces[]= "kqrbnp.PNBRQK";

std::string
CMove::ToShortString() const
{
    std::stringstream ss;
    assert(m_captured != IV);

    ss << m_from;
    ss << m_to;

    if (m_promoted != EM) {
	ss << (char)tolower(pieces[m_promoted + 6]);
    }
    return ss.str();
}

std::string
CMove::ToLongString() const
{
    std::stringstream ss;
    assert(m_captured != IV);

    ss << pieces[m_piece + 6];
    ss << m_from;
    if (m_captured != EM)
	ss << "*";
    else
	ss << "-";

    ss << m_to;

    if (m_promoted != EM) {
	ss << "=";
	ss << (char)tolower(pieces[m_promoted + 6]);
    }
    return ss.str();
}

// Returns NULL if error
const char*
CMove::FromString(const char* s)
{
    if (m_from.FromString(s) || m_to.FromString(s + 2))
	return NULL;

    s+= 4;

    m_piece= EM;
    m_captured= EM;
    m_promoted= EM;

    if (m_to.row() == 1) {
	switch (tolower(s[0])) {
	    case 'q':
		m_promoted= BQ;
		s++;
		break;
	    case 'r':
		m_promoted= BR;
		s++;
		break;
	    case 'b':
		m_promoted= BB;
		s++;
		break;
	    case 'n':
		m_promoted= BN;
		s++;
		break;
	    case ' ':
		break;
	    case '\0':
		break;
	    default:
		return NULL;
	}
    } else if (m_to.row() == 8) {
	std::cout << "DING 1 " << std::endl;
	switch (tolower(s[0])) {
	    case 'q':
		std::cout << "DING" << std::endl;
		m_promoted= WQ;
		s++;
		break;
	    case 'r':
		m_promoted= WR;
		s++;
		break;
	    case 'b':
		m_promoted= WB;
		s++;
		break;
	    case 'n':
		m_promoted= WN;
		s++;
		break;
	    case ' ':
		std::cout << "DING 2" << std::endl;
		break;
	    case '\0':
		break;
	    default:
		return NULL;
	}
    }

    while (s[0] == ' ')
	s++;

    return s;
} /* end of FromString */
