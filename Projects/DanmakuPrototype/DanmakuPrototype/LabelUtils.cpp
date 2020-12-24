#include "LabelUtils.h"

void LabelUtils::SetText(std::string labelName, std::string newText) {
	for (auto& entity : EntityManager::GetEntities()) {
		if (entity->GetEntityType() == EntityTypeEnum::LABEL && entity->GetName() == labelName)
			entity->GetComponent<TextComponent>()->SetText(newText);
	}
}