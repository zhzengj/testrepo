#ifndef _H_CONST_H_
#define _H_CONST_H_

class QDomDocument;
class QString;

namespace ZJ
{
	extern const wchar_t * XmlAccountId;
	extern const wchar_t * XmlTianyaForumId;

	enum {
		JA_Enable	= 0x01,
		JA_Login	= 0x02
	};

	bool openXml(QDomDocument & doc, const QString & fileName);
}

#endif