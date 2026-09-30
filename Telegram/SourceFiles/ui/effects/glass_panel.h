/*
Custom liquid-glass painter (personal fork).
*/
#pragma once

#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QRect>

namespace Ui {

struct GlassStyle {
	int radius = 22;
	QColor tint = QColor(255, 255, 255, 34);
	QColor sheenTop = QColor(255, 255, 255, 70);
	QColor sheenBottom = QColor(255, 255, 255, 6);
	QColor edgeLight = QColor(255, 255, 255, 215);
	QColor edgeDark = QColor(255, 255, 255, 30);
	QColor innerShadow = QColor(0, 0, 0, 40);
};

// `blurredBackdrop` is an already blurred picture of whatever is behind
// the panel, same size as `rect` (or larger; it is stretched to fit).
// Pass a null image to get a tint-only glass.
void PaintGlass(
	QPainter &p,
	const QRect &rect,
	const QImage &blurredBackdrop,
	const GlassStyle &st = GlassStyle());

} // namespace Ui
