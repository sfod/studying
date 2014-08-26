#include "actor_factory.hpp"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

static ActorId g_actor_id = 0;

ActorFactory::ActorFactory()
{
}

// @todo init actor from resource
std::shared_ptr<Actor> ActorFactory::create_actor(const char *resource)
{
    QFile file(resource);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return std::shared_ptr<Actor>();
    }

    std::shared_ptr<Actor> actor(new Actor(++g_actor_id));
    int progress = 0;

    QXmlStreamReader xml_reader(&file);
    QXmlStreamReader::TokenType token;
    while (!xml_reader.atEnd()) {
        token = xml_reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            qDebug() << "xml elem: " << xml_reader.name();
            if (progress == 0) {
                actor->init(xml_reader.attributes());
                progress = 1;
            }
            else if (progress == 1) {

            }
            continue;
        }
    }

    return actor;
}
