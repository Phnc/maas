package com.ref;

import com.change_vision.jude.api.inf.AstahAPI;
import com.change_vision.jude.api.inf.exception.*;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.project.ModelFinder;
import com.change_vision.jude.api.inf.project.ProjectAccessor;
import com.ref.exceptions.FDRException;
import com.ref.exceptions.ParsingException;
import com.ref.exceptions.WellFormedException;
import com.ref.ui.CheckingProgressBar;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws ProjectNotFoundException, ProjectLockedException, LicenseNotFoundException, IOException, ClassNotFoundException, NonCompatibleException, InvalidExportImageException, InvalidUsingException, FDRException, WellFormedException, ParsingException {
        ProjectAccessor projectAccessor = AstahAPI.getAstahAPI().getProjectAccessor();
        projectAccessor.open("src/main/resources/e-commerc.asta");
        INamedElement[] findElements = findElements(projectAccessor);

        IActivityDiagram ad = (IActivityDiagram) findElements[0];

        ActivityController ac = ActivityController.getInstance();
        CheckingProgressBar bar = new CheckingProgressBar();
        ac.AstahInvocation(ad, ActivityController.VerificationType.DEADLOCK, bar);

        bar.dispose();

        projectAccessor.save();
        projectAccessor.close();
    }

    public static INamedElement[] findElements(ProjectAccessor projectAccessor) throws ProjectNotFoundException {
        INamedElement[] foundElements = projectAccessor.findElements(new ModelFinder() {
            public boolean isTarget(INamedElement namedElement) {
                return namedElement instanceof IActivityDiagram;
            }
        });
        return foundElements;
    }
}
