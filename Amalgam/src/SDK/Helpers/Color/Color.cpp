#include "Color.h"
#include "../../Vars.h"
#include "../../../Features/Players/PlayerUtils.h"

Color_t CColor::GetTeamColor(int iLocalTeam, int iTargetTeam, bool bRelative)
{
	if (bRelative)
		return iLocalTeam == iTargetTeam ? Vars::Colors::Team.Value : Vars::Colors::Enemy.Value;
	else
	{
		switch (iTargetTeam)
		{
		case TF_TEAM_RED: return Vars::Colors::TeamRed.Value;
		case TF_TEAM_BLUE: return Vars::Colors::TeamBlu.Value;
		}
	}

	return { 255, 255, 255, 255 };
}

// Add this function
Color_t CColor::GetEntityNameColor(CTFPlayer* pLocal, CBaseEntity* pEntity, bool bRelative)
{
	int iLocalTeam = pLocal->m_iTeamNum();
	int iTargetTeam = pEntity->m_iTeamNum();

	if (pEntity == pLocal)
	{
		return Vars::Colors::LocalName.Value;
	}
	else if (pEntity->entindex() == G::AimTarget.m_iEntIndex )
	{
		return Vars::Colors::TargetName.Value;
	}

	if (pEntity->IsPlayer())
	{
		if (pEntity->As<CTFPlayer>()->IsFriend())
		{
			return Vars::Colors::FriendName.Value;
		}
		else
		{
			if (bRelative)
				return iLocalTeam == iTargetTeam ? Vars::Colors::TeamName.Value : Vars::Colors::EnemyName.Value;
			else
			{
				switch (iTargetTeam)
				{
				case 2: return Vars::Colors::TeamRedName.Value;
				case 3: return Vars::Colors::TeamBluName.Value;
				}
			}
		}
	}
	else
	{
		if (bRelative)
			return iLocalTeam == iTargetTeam ? Vars::Colors::TeamName.Value : Vars::Colors::EnemyName.Value;
		else
		{
			switch (iTargetTeam)
			{
			case 2: return Vars::Colors::TeamRedName.Value;
			case 3: return Vars::Colors::TeamBluName.Value;
			}
		}
	}

	return { 255, 255, 255, 255 };
}

Color_t CColor::GetEntityDrawColor(CTFPlayer* pLocal, CBaseEntity* pEntity, bool bRelative, CBaseEntity* pTarget, int* pType)
{
	Color_t out = GetTeamColor(pLocal->m_iTeamNum(), pEntity->m_iTeamNum(), bRelative);
	if (pType) *pType = 1;

	if (pEntity->IsPlayer())
	{
		auto pPlayer = pEntity->As<CTFPlayer>();

		if (pLocal == pPlayer)
		{
			out = Vars::Colors::Local.Value;
			if (pType) *pType = 2;
		}
		else if (H::Entities.IsFriend(pPlayer->entindex()))
		{
			//out = F::PlayerUtils.m_vTags[F::PlayerUtils.TagToIndex(FRIEND_TAG)].m_tColor;
			if (pType) *pType = 3;
		}
		/*else if (H::Entities.InParty(pPlayer->entindex()))
		{
			out = F::PlayerUtils.m_vTags[F::PlayerUtils.TagToIndex(PARTY_TAG)].m_tColor;
			if (pType) *pType = 4;
		}*/
		/*/else if (auto pTag = F::PlayerUtils.GetSignificantTag(pPlayer->entindex()))
		{
			out = pTag->m_tColor;
			if (pType) *pType = 5;
		}*/
	}

	if (pTarget && pTarget->entindex() == G::AimTarget.m_iEntIndex)
	{
		out = Vars::Colors::Target.Value;
		if (pType) *pType = 6;
	}

	return out;
}

Color_t CColor::GetScoreboardColor(int iIndex)
{
	Color_t out = { 0, 0, 0, 0 };

	if (iIndex == I::EngineClient->GetLocalPlayer())
		out = Vars::Colors::Local.Value;
	else if (H::Entities.IsFriend(iIndex))
		out = F::PlayerUtils.m_vTags[F::PlayerUtils.TagToIndex(FRIEND_TAG)].m_tColor;
	else if (H::Entities.InParty(iIndex))
		out = F::PlayerUtils.m_vTags[F::PlayerUtils.TagToIndex(PARTY_TAG)].m_tColor;
	else if (auto pTag = F::PlayerUtils.GetSignificantTag(iIndex))
		out = pTag->m_tColor;

	return out;
}