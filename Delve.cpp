#include "Delve.hpp"


void Delve::UpgradeFlareRadius()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeFlareDuration()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 9);
	PacketBuilder::Send(p);
}

void Delve::UpgradeFlareMax()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeDynamiteRadius()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeDynamiteDamage()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeDynamiteMax()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeSulphiteCapacity()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeDarknessResistance()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}

void Delve::UpgradeLightRadius()
{
	PacketWriter* p = PacketBuilder::UpgradeDelveStat(0, 4);
	PacketBuilder::Send(p);
}