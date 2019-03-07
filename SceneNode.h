#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>

class SceneNode : private sf::NonCopyable, public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr; // то же самое, что и (std::unique_ptr<SceneNode> Ptr), только теперь € могу объ€вить вот так: (SceneNode::Ptr);

public:
	SceneNode();

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

private:
	virtual void updateCurrent(sf::Time dt);
	void updateChild(sf::Time dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChild(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Ptr> mCildren;
	SceneNode* mParent;
};

#endif // !SCENENODE_H
