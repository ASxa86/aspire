#include <aspire/Aspire.h>

using aspire::Aspire;

void Aspire::writeFile(QObject* object, const QUrl& url) const
{
	const auto file = url.toLocalFile();
	aspire::WriteFileQML(object, file.toStdString());
}