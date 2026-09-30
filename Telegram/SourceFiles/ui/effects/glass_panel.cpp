/*
Custom liquid-glass painter (personal fork).
*/
#include "ui/effects/glass_panel.h"

#include <QtGui/QLinearGradient>
#include <QtGui/QPainterPath>

namespace Ui {

void PaintGlass(
		QPainter &p,
		const QRect &rect,
		const QImage &blurredBackdrop,
		const GlassStyle &st) {
	if (rect.isEmpty()) {
		return;
	}
	auto hq = QPainter::RenderHints(QPainter::Antialiasing
		| QPainter::SmoothPixmapTransform);
	p.save();
	p.setRenderHints(hq, true);

	const auto r = QRectF(rect);
	const auto radius = qreal(st.radius);
	auto shape = QPainterPath();
	shape.addRoundedRect(r, radius, radius);

	// 1. Blurred backdrop, slightly over-saturated look via extra tint.
	p.setClipPath(shape);
	if (!blurredBackdrop.isNull()) {
		p.drawImage(r, blurredBackdrop);
	}

	// 2. Base tint.
	p.fillPath(shape, st.tint);

	// 3. Vertical sheen: bright at the top, fading out.
	auto sheen = QLinearGradient(r.topLeft(), r.bottomLeft());
	sheen.setColorAt(0., st.sheenTop);
	sheen.setColorAt(0.45, QColor(255, 255, 255, 14));
	sheen.setColorAt(1., st.sheenBottom);
	p.fillPath(shape, sheen);

	// 4. Soft inner shadow along the bottom for thickness.
	auto depth = QLinearGradient(r.bottomLeft(), r.topLeft());
	depth.setColorAt(0., st.innerShadow);
	depth.setColorAt(0.18, QColor(0, 0, 0, 0));
	p.fillPath(shape, depth);
	p.setClipping(false);

	// 5. Specular rim: bright top-left and bottom-right, dim between.
	auto rim = QLinearGradient(r.topLeft(), r.bottomRight());
	rim.setColorAt(0., st.edgeLight);
	rim.setColorAt(0.35, st.edgeDark);
	rim.setColorAt(0.65, st.edgeDark);
	rim.setColorAt(1., QColor(
		st.edgeLight.red(),
		st.edgeLight.green(),
		st.edgeLight.blue(),
		st.edgeLight.alpha() * 3 / 5));
	auto pen = QPen(QBrush(rim), 1.25);
	p.setPen(pen);
	p.setBrush(Qt::NoBrush);
	p.drawRoundedRect(r.adjusted(0.6, 0.6, -0.6, -0.6), radius, radius);

	p.restore();
}

} // namespace Ui
