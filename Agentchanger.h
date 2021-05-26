#include "Thanatos.h"
#include "Inih/INIReader.h"
#include "SDK/ItemDefinitionIndex.h"

/*constexpr std::array models
{
    "models/player/custom_player/legacy/ctm_fbi_variantb.mdl",
        "models/player/custom_player/legacy/ctm_fbi_variantf.mdl",
        "models/player/custom_player/legacy/ctm_fbi_variantg.mdl",
        "models/player/custom_player/legacy/ctm_fbi_varianth.mdl",
        "models/player/custom_player/legacy/ctm_sas_variantf.mdl",
        "models/player/custom_player/legacy/ctm_st6_variante.mdl",
        "models/player/custom_player/legacy/ctm_st6_variantg.mdl",
        "models/player/custom_player/legacy/ctm_st6_varianti.mdl",
        "models/player/custom_player/legacy/ctm_st6_variantk.mdl",
        "models/player/custom_player/legacy/ctm_st6_variantm.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantf.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantg.mdl",
        "models/player/custom_player/legacy/tm_balkan_varianth.mdl",
        "models/player/custom_player/legacy/tm_balkan_varianti.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantj.mdl",
        "models/player/custom_player/legacy/tm_leet_variantf.mdl",
        "models/player/custom_player/legacy/tm_leet_variantg.mdl",
        "models/player/custom_player/legacy/tm_leet_varianth.mdl",
        "models/player/custom_player/legacy/tm_leet_varianti.mdl",
        "models/player/custom_player/legacy/tm_phoenix_variantf.mdl",
        "models/player/custom_player/legacy/tm_phoenix_variantg.mdl",
        "models/player/custom_player/legacy/tm_phoenix_varianth.mdl",

        "models/player/custom_player/legacy/tm_pirate.mdl",
        "models/player/custom_player/legacy/tm_pirate_varianta.mdl",
        "models/player/custom_player/legacy/tm_pirate_variantb.mdl",
        "models/player/custom_player/legacy/tm_pirate_variantc.mdl",
        "models/player/custom_player/legacy/tm_pirate_variantd.mdl",
        "models/player/custom_player/legacy/tm_anarchist.mdl",
        "models/player/custom_player/legacy/tm_anarchist_varianta.mdl",
        "models/player/custom_player/legacy/tm_anarchist_variantb.mdl",
        "models/player/custom_player/legacy/tm_anarchist_variantc.mdl",
        "models/player/custom_player/legacy/tm_anarchist_variantd.mdl",
        "models/player/custom_player/legacy/tm_balkan_varianta.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantb.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantc.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantd.mdl",
        "models/player/custom_player/legacy/tm_balkan_variante.mdl",
        "models/player/custom_player/legacy/tm_jumpsuit_varianta.mdl",
        "models/player/custom_player/legacy/tm_jumpsuit_variantb.mdl",
        "models/player/custom_player/legacy/tm_jumpsuit_variantc.mdl",

        "models/player/custom_player/legacy/tm_phoenix_varianti.mdl",
        "models/player/custom_player/legacy/ctm_st6_variantj.mdl",
        "models/player/custom_player/legacy/ctm_st6_variantl.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantk.mdl",
        "models/player/custom_player/legacy/tm_balkan_variantl.mdl",
        "models/player/custom_player/legacy/ctm_swat_variante.mdl",
        "models/player/custom_player/legacy/ctm_swat_variantf.mdl",
        "models/player/custom_player/legacy/ctm_swat_variantg.mdl",
        "models/player/custom_player/legacy/ctm_swat_varianth.mdl",
        "models/player/custom_player/legacy/ctm_swat_varianti.mdl",
        "models/player/custom_player/legacy/ctm_swat_variantj.mdl",
        "models/player/custom_player/legacy/tm_professional_varf.mdl",
        "models/player/custom_player/legacy/tm_professional_varf1.mdl",
        "models/player/custom_player/legacy/tm_professional_varf2.mdl",
        "models/player/custom_player/legacy/tm_professional_varf3.mdl",
        "models/player/custom_player/legacy/tm_professional_varf4.mdl",
        "models/player/custom_player/legacy/tm_professional_varg.mdl",
        "models/player/custom_player/legacy/tm_professional_varh.mdl",
        "models/player/custom_player/legacy/tm_professional_vari.mdl",
        "models/player/custom_player/legacy/tm_professional_varj.mdl"
};*/

extern Thanatos thanatos;

void Thanatos::AgentChanger(ClientFrameStage_t curStage)
{
	if (!localPlayer || !EngineClient->isInGame()) return;
    int agentIndex = *(int*)(localPlayer + netvars::m_nModelIndex);

	switch (localPlayer->GetTeam())
	{
	case 2: // Terrorists
        agentIndex = ModelInfoClient->GetModelIndex("models/player/custom_player/legacy/tm_professional_varf4.mdl");
		break;
	case 3: // Antiterrorists
        agentIndex = ModelInfoClient->GetModelIndex("models/player/custom_player/legacy/ctm_st6_variantm.mdl");
		break;
	default:
		break;
	}
}